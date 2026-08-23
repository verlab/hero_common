#!/usr/bin/env python3
"""HeRo swarm on official Genesis World.

https://github.com/Genesis-Embodied-AI/genesis-world
"""
from __future__ import print_function

import argparse
import json
import math
import os
import re
import socket
import sys
import tempfile
import threading
import time

WHEEL_SEP = 0.0646
WHEEL_RADIUS = 0.025
BODY_RADIUS = 0.037
KIN_Z = 0.045
ARENA_HALF = 1.70
RANGE_MIN = 0.037
RANGE_MAX = 0.50
N_RAYS = 16
TICKS_REV = 288.0


def _np(x):
    import numpy as np
    if hasattr(x, "detach"):
        x = x.detach()
    if hasattr(x, "cpu"):
        x = x.cpu().numpy()
    return np.asarray(x, dtype=float).reshape(-1)


def led_palette(i, n):
    hue = (i / float(max(1, n))) * 6.0
    sector = int(hue)
    frac = hue - sector
    table = (
        (1.0, frac, 0.0),
        (1.0 - frac, 1.0, 0.0),
        (0.0, 1.0, frac),
        (0.0, 1.0 - frac, 1.0),
        (frac, 0.0, 1.0),
        (1.0, 0.0, 1.0 - frac),
    )
    r, g, b = table[min(sector, 5)]
    return (float(r), float(g), float(b))


def grid_xy(i, n, spacing=0.28):
    cols = 5 if n >= 15 else max(1, int(math.ceil(math.sqrt(n))))
    rows = int(math.ceil(n / float(cols)))
    col, row = i % cols, i // cols
    x = (col - (cols - 1) / 2.0) * spacing
    y = (row - (rows - 1) / 2.0) * spacing
    return x, y


def yaw_of_quat(q):
    w, x, y, z = [float(v) for v in q]
    return math.atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z))


def quat_of_yaw(yaw):
    return (math.cos(yaw / 2.0), 0.0, 0.0, math.sin(yaw / 2.0))


class CmdHub(object):
    """Optional ROS bridge socket. Physics and the window stay in Genesis."""

    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((host, port))
        self.sock.listen(8)
        self.sock.setblocking(False)
        self.clients = []
        self.buffers = {}
        self.lock = threading.Lock()
        self.cmds = {}

    def pump(self):
        try:
            conn, _ = self.sock.accept()
            conn.setblocking(False)
            self.clients.append(conn)
            self.buffers[conn] = ""
        except BlockingIOError:
            pass
        for conn in list(self.clients):
            try:
                chunk = conn.recv(4096)
            except BlockingIOError:
                continue
            except Exception:
                self._drop(conn)
                continue
            if not chunk:
                self._drop(conn)
                continue
            self.buffers[conn] += chunk.decode("utf-8", "replace")
            while "\n" in self.buffers[conn]:
                line, self.buffers[conn] = self.buffers[conn].split("\n", 1)
                if not line.strip():
                    continue
                try:
                    msg = json.loads(line)
                except ValueError:
                    continue
                if msg.get("type") == "cmd_vel":
                    with self.lock:
                        self.cmds[int(msg.get("id", 0))] = (
                            float(msg.get("lin", 0.0)),
                            float(msg.get("ang", 0.0)),
                            time.time(),
                        )

    def command(self, idx, fallback):
        with self.lock:
            item = self.cmds.get(idx)
        if item is None:
            return fallback
        v, w, ts = item
        if time.time() - ts > 0.5:
            return fallback
        return v, w

    def broadcast(self, payload):
        blob = (json.dumps(payload) + "\n").encode("utf-8")
        for conn in list(self.clients):
            try:
                conn.sendall(blob)
            except Exception:
                self._drop(conn)

    def _drop(self, conn):
        try:
            conn.close()
        except Exception:
            pass
        if conn in self.clients:
            self.clients.remove(conn)
        self.buffers.pop(conn, None)


def _repo_pkg(name):
    here = os.path.dirname(os.path.abspath(__file__))
    return os.path.normpath(os.path.join(here, "..", "..", name))


def description_root():
    return _repo_pkg("hero_description")


def gazebo_root():
    return _repo_pkg("hero_gazebo")


def materialize_hero_urdf(variant, hat_rgba=None, suffix="", physics=False):
    """Resolve package://hero_description and color only hat_link (Gazebo LED)."""
    desc = description_root()
    src = os.path.join(desc, "robot", variant + ".urdf")
    if not os.path.isfile(src):
        raise FileNotFoundError("hero_description URDF missing: %s" % src)
    text = open(src, "r", encoding="utf-8").read()
    mesh_root = desc.rstrip("/") + "/"
    text = text.replace("package://hero_description/", mesh_root)
    text = re.sub(r"<gazebo\b[\s\S]*?</gazebo>", "", text)
    text = re.sub(r"<transmission\b[\s\S]*?</transmission>", "", text)
    if hat_rgba is not None:
        r, g, b = hat_rgba[0], hat_rgba[1], hat_rgba[2]
        a = hat_rgba[3] if len(hat_rgba) > 3 else 1.0
        mat = (
            '\n      <material name="hat_led">'
            '<color rgba="%.4f %.4f %.4f %.4f"/>'
            "</material>" % (r, g, b, a)
        )
        text, n = re.subn(
            r'(<link name="hat_link">\s*<visual>[\s\S]*?</geometry>)',
            r"\1" + mat,
            text,
            count=1,
        )
        if n != 1:
            raise RuntimeError("could not inject hat_link material into %s" % src)
    # Hat mesh must not collide (Gazebo sets maxContacts=0). It flips the body.
    text = re.sub(
        r'(<link name="hat_link">[\s\S]*?)</link>',
        lambda m: re.sub(r"<collision\b[\s\S]*?</collision>", "", m.group(0)),
        text,
        count=1,
    )
    if not physics:
        # Kinematic demo: one body cylinder, wheels visual-only (no extra DOFs).
        text = re.sub(
            r'(<link name="(?:left|right)_wheel_link">[\s\S]*?)</link>',
            lambda m: re.sub(r"<collision\b[\s\S]*?</collision>", "", m.group(0)),
            text,
        )
        text = text.replace('type="continuous"', 'type="fixed"')
    if physics:
        # Front/rear skids: real HeRo scrapes the chassis; two wheels alone tip over.
        skids = (
            '\n    <collision>'
            '<origin xyz="0.020 0 0.001" rpy="0 0 0"/>'
            '<geometry><sphere radius="0.008"/></geometry>'
            "</collision>"
            '\n    <collision>'
            '<origin xyz="-0.020 0 0.001" rpy="0 0 0"/>'
            '<geometry><sphere radius="0.008"/></geometry>'
            "</collision>"
        )
        text, n_skid = re.subn(
            r'(<link name="base_link">[\s\S]*?</collision>)',
            r"\1" + skids,
            text,
            count=1,
        )
        if n_skid != 1:
            raise RuntimeError("could not inject chassis skids into %s" % src)
    out = os.path.join(tempfile.gettempdir(), "hero_genesis_%s%s.urdf" % (variant, suffix))
    with open(out, "w", encoding="utf-8") as fh:
        fh.write(text)
    return out


def add_arena(scene, gs, arena_id, physics):
    """Hollow wall visual from hero_gazebo plus invisible box colliders."""
    obj = os.path.join(gazebo_root(), "worlds", "models", "arena_%d" % arena_id, "arena.obj")
    if not os.path.isfile(obj):
        raise FileNotFoundError("hero_gazebo arena missing: %s" % obj)
    # Visual only: URDF+watertight wrap filled the 4x4x0.3m interior and buried the robots.
    scene.add_entity(
        gs.morphs.Mesh(
            file=obj,
            pos=(0.0, 0.0, 0.0),
            euler=(0.0, 0.0, -270.0),
            collision=False,
            convexify=False,
            decimate=False,
            fixed=True,
        )
    )
    print("Arena visual: %s" % obj, flush=True)
    wall_h = 0.15
    wall_t = 0.12
    wall_z = 0.15
    span = 4.0
    inner = 1.88
    for pos, size in (
        ((0.0, inner, wall_z), (span, wall_t, wall_h * 2)),
        ((0.0, -inner, wall_z), (span, wall_t, wall_h * 2)),
        ((inner, 0.0, wall_z), (wall_t, span - 2.0 * wall_t, wall_h * 2)),
        ((-inner, 0.0, wall_z), (wall_t, span - 2.0 * wall_t, wall_h * 2)),
    ):
        scene.add_entity(
            gs.morphs.Box(pos=pos, size=size, fixed=True, visualization=False)
        )


def wrap_pi(angle):
    return (angle + math.pi) % (2.0 * math.pi) - math.pi


def wheel_speeds(v, w):
    """cmd_vel (m/s, rad/s) -> left/right wheel angular velocities."""
    half = 0.5 * WHEEL_SEP
    return (v - w * half) / WHEEL_RADIUS, (v + w * half) / WHEEL_RADIUS


def circle_loop_cmds(robots, radius=1.05, omega=0.28, cx=0.0, cy=0.0):
    """Radial expand, then keep looping CCW on the ring."""
    n = max(1, len(robots))
    desired_gap = 2.0 * math.pi / n
    cruise = radius * omega
    polar = []
    for robot in robots:
        dx = robot["x"] - cx
        dy = robot["y"] - cy
        rad = math.hypot(dx, dy)
        spoke = 2.0 * math.pi * int(robot["id"]) / n
        th = spoke if rad < 0.10 else math.atan2(dy, dx)
        polar.append((th, rad, robot))
    polar.sort(key=lambda item: item[0])
    cmds = {}
    for i, (th, rad, robot) in enumerate(polar):
        gap = wrap_pi(polar[(i + 1) % n][0] - th)
        if gap <= 1e-4:
            gap += 2.0 * math.pi
        v_rad = 0.50 * (radius - rad)
        if rad < radius - 0.12:
            v_tan = 0.0
        else:
            v_tan = cruise * max(0.40, min(1.35, gap / desired_gap))
        vx = v_rad * math.cos(th) - v_tan * math.sin(th)
        vy = v_rad * math.sin(th) + v_tan * math.cos(th)
        x, y, yaw = robot["x"], robot["y"], robot["yaw"]
        for other in robots:
            if other["id"] == robot["id"]:
                continue
            ox, oy = x - other["x"], y - other["y"]
            dist = math.hypot(ox, oy)
            if 1e-4 < dist < 0.15:
                mag = 0.45 * (0.15 - dist) / 0.15
                vx += mag * ox / dist
                vy += mag * oy / dist
        speed = math.hypot(vx, vy)
        heading = math.atan2(vy, vx) if speed > 1e-4 else yaw
        err = wrap_pi(heading - yaw)
        v = speed * math.cos(err)
        if abs(err) > 0.8:
            v *= 0.15
        cmds[int(robot["id"])] = (
            max(-0.02, min(0.08, v)),
            max(-1.1, min(1.1, 2.1 * err)),
        )
    return cmds


def configure_drive(entity):
    left = entity.get_joint("left_wheel_joint")
    right = entity.get_joint("right_wheel_joint")
    dofs = [left.dofs_idx_local[0], right.dofs_idx_local[0]]
    entity.set_dofs_kp((0.0, 0.0), dofs)
    entity.set_dofs_kv((6.0, 6.0), dofs)
    # Gazebo wheel torque is ~0.03–0.1 N·m; 0.5 N·m flips a 140 g HeRo.
    entity.set_dofs_force_range((-0.04, -0.04), (0.04, 0.04), dofs)
    for link in entity.links:
        name = getattr(link, "name", "")
        try:
            if "wheel" in name:
                link.set_friction(1.0)
            else:
                link.set_friction(0.06)
        except Exception:
            pass
    return dofs


def rpy_of_quat(q):
    w, x, y, z = [float(v) for v in q]
    roll = math.atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y))
    sinp = max(-1.0, min(1.0, 2.0 * (w * y - z * x)))
    pitch = math.asin(sinp)
    yaw = math.atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z))
    return roll, pitch, yaw


def recover_if_tipped(robot):
    entity = robot["entity"]
    quat = _np(entity.get_quat())
    roll, pitch, yaw = rpy_of_quat(quat)
    if abs(roll) < 0.6 and abs(pitch) < 0.6:
        return
    pos = _np(entity.get_pos())
    entity.set_pos((float(pos[0]), float(pos[1]), 0.022))
    entity.set_quat(quat_of_yaw(yaw))
    try:
        entity.set_dofs_velocity(None)
    except Exception:
        pass


def pick_backend(name, gs):
    name = (name or "auto").lower()
    if name == "cpu":
        return gs.cpu
    # Apple Silicon has gs.metal, but this interactive 20-robot scene is much
    # faster on CPU (~45 FPS vs ~2 FPS). Force GPU with --backend metal.
    if name in ("gpu", "metal") and sys.platform == "darwin" and hasattr(gs, "metal"):
        return gs.metal
    if name in ("gpu", "cuda") and hasattr(gs, "gpu"):
        return gs.gpu
    if name == "metal" and hasattr(gs, "metal"):
        return gs.metal
    if hasattr(gs, "gpu"):
        try:
            import torch
            if torch.cuda.is_available():
                return gs.gpu
        except Exception:
            pass
    return gs.cpu


def build_scene(gs, args):
    physics = bool(args.physics)
    scene = gs.Scene(
        show_viewer=bool(args.vis),
        sim_options=gs.options.SimOptions(
            dt=0.01,
            substeps=10 if physics else 1,
            gravity=(0.0, 0.0, -9.81) if physics else (0.0, 0.0, 0.0),
        ),
        rigid_options=gs.options.RigidOptions(
            enable_collision=True,
            enable_self_collision=False,
            enable_joint_limit=physics,
            disable_constraint=False,
            max_collision_pairs=400 if not physics else 2000,
            iterations=12 if not physics else 50,
            ls_iterations=8 if not physics else 50,
        ),
        vis_options=gs.options.VisOptions(shadow=False),
        viewer_options=gs.options.ViewerOptions(
            camera_pos=(0.0, -4.2, 3.4),
            camera_lookat=(0.0, 0.0, 0.0),
            camera_fov=50,
            realtime_factor=None,
            enable_help_text=False,
        ),
    )
    scene.add_entity(gs.morphs.Plane(collision=physics))
    add_arena(scene, gs, int(args.arena), physics)

    spawn_z = KIN_Z if not physics else 0.022
    robots = []
    for i in range(args.num_robots):
        x, y = grid_xy(i, args.num_robots)
        hat = led_palette(i, args.num_robots)
        urdf = materialize_hero_urdf(
            args.model, hat_rgba=hat + (1.0,), suffix="_%d" % i, physics=physics
        )
        entity = scene.add_entity(
            gs.morphs.URDF(
                file=urdf,
                pos=(x, y, spawn_z),
                collision=True,
                convexify=False,
                links_to_keep=("hat_link",) if physics else (),
                default_armature=0.001 if physics else 0.0,
            ),
        )
        robots.append({
            "id": i,
            "entity": entity,
            "x": x,
            "y": y,
            "yaw": 0.0,
            "z": spawn_z,
            "v": 0.0,
            "w": 0.0,
            "wl": 0.0,
            "wr": 0.0,
            "left_ticks": 0.0,
            "right_ticks": 0.0,
            "wheel_dofs": None,
        })
    print(
        "Loaded %d x %s from hero_description (%s, LED on hat_link)."
        % (
            args.num_robots,
            args.model,
            "physics + gravity" if physics else "kinematic + body collision",
        ),
        flush=True,
    )
    scene.build()
    if physics:
        for robot in robots:
            robot["wheel_dofs"] = configure_drive(robot["entity"])
    return scene, robots


def _cmd_for(robot, idx, n, pattern, circle_fb, hub):
    if pattern == "still":
        fallback = (0.0, 0.0)
    elif pattern == "spin":
        fallback = (0.0, 0.6 if idx % 2 == 0 else -0.6)
    elif pattern == "circle":
        fallback = circle_fb.get(idx, (0.0, 0.0))
    else:
        fallback = (0.07, 0.45 if idx % 2 == 0 else -0.45)
    return hub.command(idx, fallback) if hub else fallback


def apply_drive(robots, hub, pattern, t, physics, dt):
    circle_fb = circle_loop_cmds(robots) if pattern == "circle" else {}
    n = len(robots)
    for i, robot in enumerate(robots):
        v, w = _cmd_for(robot, i, n, pattern, circle_fb, hub)
        robot["v"], robot["w"] = v, w
        wl, wr = wheel_speeds(v, w)
        robot["wl"], robot["wr"] = wl, wr
        entity = robot["entity"]
        if physics:
            entity.control_dofs_velocity((wl, wr), robot["wheel_dofs"])
            continue
        yaw = robot["yaw"] + w * dt
        x = robot["x"] + v * math.cos(yaw) * dt
        y = robot["y"] + v * math.sin(yaw) * dt
        x = max(-ARENA_HALF, min(ARENA_HALF, x))
        y = max(-ARENA_HALF, min(ARENA_HALF, y))
        entity.set_pos((x, y, KIN_Z))
        entity.set_quat(quat_of_yaw(yaw))
        robot["x"], robot["y"], robot["yaw"], robot["z"] = x, y, yaw, KIN_Z


def read_state(robots):
    for robot in robots:
        entity = robot["entity"]
        pos = _np(entity.get_pos())
        quat = _np(entity.get_quat())
        robot["x"] = float(pos[0])
        robot["y"] = float(pos[1])
        robot["z"] = float(pos[2]) if len(pos) > 2 else 0.0
        robot["yaw"] = yaw_of_quat(quat)
        try:
            q = _np(entity.get_dofs_position(robot["wheel_dofs"]))
            robot["left_ticks"] = float(q[0]) * TICKS_REV / (2.0 * math.pi)
            robot["right_ticks"] = float(q[1]) * TICKS_REV / (2.0 * math.pi)
        except Exception:
            pass


def state_payload(robots, t):
    out = []
    for robot in robots:
        out.append({
            "id": robot["id"],
            "x": robot["x"],
            "y": robot["y"],
            "z": robot["z"],
            "yaw": robot["yaw"],
            "v": robot["v"],
            "w": robot["w"],
            "wl": robot["wl"],
            "wr": robot["wr"],
            "left_ticks": robot["left_ticks"],
            "right_ticks": robot["right_ticks"],
            "ranges": [RANGE_MAX] * N_RAYS,
        })
    return {"type": "state", "t": t, "robots": out}


def main():
    parser = argparse.ArgumentParser(description="HeRo on Genesis World")
    parser.add_argument("--num-robots", type=int, default=20)
    parser.add_argument(
        "--arena",
        type=int,
        default=0,
        help="hero_gazebo arena id (0-7), same models as gazebo_wizard",
    )
    parser.add_argument("--backend", default="auto")
    parser.add_argument("--vis", action="store_true", default=True)
    parser.add_argument("--no-vis", action="store_true")
    parser.add_argument("--pattern", default="circle")
    parser.add_argument(
        "--physics",
        action="store_true",
        help="Wheel contacts + gravity (slower, can tip). Default is kinematic.",
    )
    parser.add_argument(
        "--no-physics",
        action="store_true",
        help="Kinematic unicycle (default). Used by the circle-line demo.",
    )
    parser.add_argument(
        "--model",
        default="hero_light",
        help="URDF in hero_description/robot/ without suffix (hero_light, hero, hero_laser, hero_imu)",
    )
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=11312)
    parser.add_argument("--steps", type=int, default=0, help="0 = run until the viewer closes")
    args = parser.parse_args()
    if args.no_vis:
        args.vis = False
    if args.no_physics:
        args.physics = False

    import genesis as gs

    backend = pick_backend(args.backend, gs)
    print("Using Genesis World from", os.path.dirname(gs.__file__), flush=True)
    print("gs.init(backend=%s)  n=%d  viewer=%s" % (backend, args.num_robots, args.vis), flush=True)
    gs.init(backend=backend)

    scene, robots = build_scene(gs, args)
    hub = None
    try:
        hub = CmdHub(args.host, args.port)
        print("ROS bridge socket on %s:%d" % (args.host, args.port), flush=True)
    except OSError as exc:
        print("ROS socket not bound (%s); viewer-only." % exc, flush=True)

    dt = 0.01
    n = 0
    print(
        "Genesis viewer: arena_%d, %s, pattern=%s"
        % (int(args.arena), "physics" if args.physics else "kinematic", args.pattern),
        flush=True,
    )
    try:
        while True:
            if hub:
                hub.pump()
            apply_drive(robots, hub, args.pattern, n * dt, args.physics, dt)
            scene.step()
            if args.physics:
                for robot in robots:
                    recover_if_tipped(robot)
            read_state(robots)
            if not args.physics:
                for robot in robots:
                    if abs(robot["z"] - KIN_Z) > 0.002:
                        robot["z"] = KIN_Z
                        robot["entity"].set_pos((robot["x"], robot["y"], KIN_Z))
            if hub and (args.physics or n % 2 == 0):
                hub.broadcast(state_payload(robots, n * dt))
            n += 1
            if args.steps and n >= args.steps:
                break
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
