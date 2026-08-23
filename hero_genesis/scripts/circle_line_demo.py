#!/usr/bin/env python3
"""Drive HeRos in a single-file circle inside the Genesis arena.

Formation avoids crossing the pack:
  1. Each robot expands along its own radial spoke (no chords through the center).
  2. On the ring they only move tangentially and keep a uniform gap to the
     neighbor ahead (convoy), plus short-range repulsion.
  3. When spacing is stable they cruise around the circle together.
"""
from __future__ import print_function

import argparse
import json
import math
import socket
import time

SAFE = 0.15
EXPAND_BAND = 0.12


def wrap_pi(angle):
    return (angle + math.pi) % (2.0 * math.pi) - math.pi


def polar_of(robot, cx, cy, spoke):
    dx = robot["x"] - cx
    dy = robot["y"] - cy
    rad = math.hypot(dx, dy)
    if rad < 0.10:
        return rad, spoke
    return rad, math.atan2(dy, dx)


def formation_cmds(robots, radius, omega, cx, cy):
    n = max(1, len(robots))
    desired_gap = 2.0 * math.pi / n
    cruise = radius * omega

    polar = []
    for robot in robots:
        spoke = 2.0 * math.pi * int(robot["id"]) / n
        rad, th = polar_of(robot, cx, cy, spoke)
        polar.append((th, rad, robot))
    polar.sort(key=lambda item: item[0])

    cmds = {}
    max_err = 0.0
    min_gap = desired_gap
    for i, (th, rad, robot) in enumerate(polar):
        th_n = polar[(i + 1) % n][0]
        gap = wrap_pi(th_n - th)
        if gap <= 1e-4:
            gap += 2.0 * math.pi
        min_gap = min(min_gap, gap)
        max_err = max(max_err, abs(radius - rad))

        v_rad = 0.50 * (radius - rad)
        if rad < radius - EXPAND_BAND:
            v_tan = 0.0
        else:
            # Always CCW on the ring; only slow down if the neighbor ahead is close.
            v_tan = cruise * max(0.40, min(1.35, gap / desired_gap))

        vx = v_rad * math.cos(th) - v_tan * math.sin(th)
        vy = v_rad * math.sin(th) + v_tan * math.cos(th)

        x, y, yaw = robot["x"], robot["y"], robot["yaw"]
        for other in robots:
            if other["id"] == robot["id"]:
                continue
            ox = x - other["x"]
            oy = y - other["y"]
            dist = math.hypot(ox, oy)
            if 1e-4 < dist < SAFE:
                mag = 0.45 * (SAFE - dist) / SAFE
                vx += mag * ox / dist
                vy += mag * oy / dist

        speed = math.hypot(vx, vy)
        heading = math.atan2(vy, vx) if speed > 1e-4 else yaw
        err = wrap_pi(heading - yaw)
        v = speed * math.cos(err)
        w = 2.1 * err
        if abs(err) > 0.8:
            v *= 0.15
        cmds[int(robot["id"])] = (
            max(-0.02, min(0.08, v)),
            max(-1.1, min(1.1, w)),
        )
    return cmds, max_err, min_gap


def send(sock, payload):
    sock.sendall((json.dumps(payload) + "\n").encode("utf-8"))


def recv_state(sock, buf):
    try:
        chunk = sock.recv(65536)
    except socket.timeout:
        return None, buf
    if not chunk:
        raise RuntimeError("engine closed the connection")
    buf += chunk.decode("utf-8", "replace")
    latest = None
    while "\n" in buf:
        line, buf = buf.split("\n", 1)
        if not line.strip():
            continue
        try:
            msg = json.loads(line)
        except ValueError:
            continue
        if msg.get("type") == "state":
            latest = msg
    return latest, buf


def main():
    parser = argparse.ArgumentParser(description="HeRo circle-line demo")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=11312)
    parser.add_argument("--radius", type=float, default=1.05)
    parser.add_argument("--omega", type=float, default=0.28)
    parser.add_argument("--cx", type=float, default=0.0)
    parser.add_argument("--cy", type=float, default=0.0)
    args = parser.parse_args()

    sock = socket.create_connection((args.host, args.port), timeout=10)
    sock.settimeout(0.2)
    print(
        "Connected to Genesis engine at %s:%d  R=%.2f"
        % (args.host, args.port, args.radius),
        flush=True,
    )

    buf = ""
    last_log = 0.0
    n_robots = 0

    while True:
        state, buf = recv_state(sock, buf)
        if state is None:
            continue
        robots = state.get("robots", [])
        if not robots:
            continue
        if n_robots != len(robots):
            n_robots = len(robots)
            print(
                "Expand to a %.2f m ring, then loop CCW forever (%d robots)."
                % (args.radius, n_robots),
                flush=True,
            )

        cmds, max_err, min_gap = formation_cmds(
            robots, args.radius, args.omega, args.cx, args.cy
        )
        for idx, (v, w) in cmds.items():
            send(sock, {"type": "cmd_vel", "id": idx, "lin": v, "ang": w})

        now = time.time()
        if now - last_log > 1.5:
            zmean = sum(r.get("z", 0.0) for r in robots) / float(len(robots))
            print(
                "err=%.3f  gap=%.2f  z=%.3f  loop"
                % (max_err, min_gap, zmean),
                flush=True,
            )
            last_log = now


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
