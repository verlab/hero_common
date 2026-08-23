---
layout: page
title: Simulate
permalink: /robot_simulation/
section: software
lead: Step 4 of 4. Two simulators share the same /hero_N topics as the real robot. Gazebo is the ROS 1 twin with a swarm wizard. Genesis World is a GPU-friendly viewer that loads the official hero_description URDF and the Gazebo arenas.
---

You can run this step without a physical robot. Controllers written for `/hero_N/cmd_vel` (and `/hero_N/velocity_controller/cmd_vel`) work on hardware, in Gazebo, and in Genesis.

| | [Gazebo](#gazebo) | [Genesis World](#genesis-world) |
|---|---|---|
| Package | `hero_gazebo` | `hero_genesis` |
| Needs | ROS 1 + Gazebo + Qt | Python 3.10–3.13 ([Genesis World](https://github.com/Genesis-Embodied-AI/genesis-world)); ROS 1 only if you want topics |
| Best on | Linux workstation with the wizard | Linux + **NVIDIA CUDA** (CPU also works; Apple Metal is slower than CPU on this scene) |
| Model | `hero_description` | same URDF / meshes; LED paints only `hat_link` |
| Arena | wizard worlds | `hero_gazebo/worlds/models/arena_0` … `arena_7` |

## Gazebo

### 1. Place an arena and a swarm

```sh
$ roslaunch hero_gazebo gazebo_wizard.launch
```

Gazebo opens with this wizard:

![HeRo wizard](https://user-images.githubusercontent.com/14208261/188969510-db02aee6-692f-40f9-902f-cb6f7a21f7ba.png)

1. Select an arena and click **Commit arena**. **Clear arena** removes it.
2. Choose how many robots and which sensors they carry.
3. Click **Commit swarm**. **Clear swarm** removes them.
4. Nudge poses in Gazebo if you want, then **Generate Launch File** to save the scene.

![Wizard sensors](https://user-images.githubusercontent.com/14208261/188969494-215a6a56-789d-4aa9-97c7-d1bbd31c1fb4.png)

Close Gazebo and the wizard when the launch file is written.

### 2. Replay the scene

Start Gazebo, then spawn the saved arena and robots:

```sh
$ roslaunch hero_gazebo gazebo_bringup.launch
$ roslaunch hero_gazebo env_spawn.launch
```

```sh
$ rostopic list
/hero_0/cmd_vel
/hero_0/laser
/hero_0/led
/hero_0/odom
/tf
```

![Gazebo swarm](https://user-images.githubusercontent.com/14208261/188969444-d0c3c0ef-be1b-4514-a5cc-db8f41a67edd.png)

<iframe width="560" height="315" src="https://www.youtube.com/embed/IO7FPEwkZkE" title="HeRo Gazebo" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

The model includes a differential-drive controller, odometry, IMU, and IR proximity (simulated as a laser).

## Genesis World

[`hero_genesis`](https://github.com/verlab/hero_common/tree/master/hero_genesis) drives a swarm in [Genesis World](https://genesis-world.readthedocs.io/). Default mode is **kinematic** (unicycle `cmd_vel`, body-cylinder collision, no gravity). Pass `--physics` only if you want wheel contacts and gravity.

The engine speaks JSON over TCP `127.0.0.1:11312`. ROS 1 is optional: `hero_genesis_node.py` republishes the same topics as Gazebo.

### 1. Install (CPU or GPU)

Python **3.10–3.13**. Create a venv at the repo root (the `.venv/` folder is gitignored):

```sh
$ cd hero_common
$ python3 -m venv hero_genesis/.venv
$ source hero_genesis/.venv/bin/activate
$ pip install -U pip
```

Install **PyTorch first**, then Genesis. Pick the wheel that matches the machine — see [pytorch.org](https://pytorch.org/get-started/locally/) if your CUDA version differs.

```sh
# CPU (Linux / Windows / smoke test)
$ pip install torch --index-url https://download.pytorch.org/whl/cpu

# NVIDIA GPU, CUDA 12.6 (typical current driver stack)
$ pip install torch --index-url https://download.pytorch.org/whl/cu126

# Apple Silicon (Metal). For this 20-robot viewer, --backend cpu is usually faster.
$ pip install torch
```

```sh
$ pip install "git+https://github.com/Genesis-Embodied-AI/genesis-world.git"
```

`hero_genesis/requirements.txt` is the same two pins.

### 2. Run the viewer

From the repository root, with the venv active:

```sh
$ python hero_genesis/scripts/genesis_engine.py \
    --vis --num-robots 20 --arena 0 --pattern circle --backend cpu --no-physics
```

Or `hero_genesis/scripts/run_local.sh` (defaults to CPU). In another terminal, the circle-line demo talks to the engine socket:

```sh
$ python hero_genesis/scripts/circle_line_demo.py --radius 1.05 --omega 0.32
```

Close the Genesis window to stop the engine.

Useful flags:

| Flag | Meaning |
|---|---|
| `--backend cpu` / `gpu` / `cuda` / `metal` / `auto` | Device. `auto` uses CUDA when `torch.cuda.is_available()`, else CPU. |
| `--arena 0` … `7` | Same meshes as the Gazebo wizard. |
| `--model hero_light` | URDF in `hero_description/robot/` (`hero`, `hero_laser`, `hero_imu`). |
| `--no-physics` | Kinematic unicycle (default for the demo). |
| `--physics` | Wheel velocities + gravity (slower, robots can tip). |
| `--no-vis` | Headless. |

### 3. NVIDIA GPU (Linux)

Genesis is fastest on **Linux + CUDA**. The GPU path is PyTorch CUDA, then `--backend gpu`.

1. Install a current [NVIDIA driver](https://www.nvidia.com/Download/index.aspx). Check it:

```sh
$ nvidia-smi
```

You want a listed GPU and a CUDA version (driver 525+ / CUDA 12.x is the usual match for the `cu126` wheel).

2. Install CUDA-enabled PyTorch **in the venv** (do not mix a CPU wheel with `--backend gpu`):

```sh
$ source hero_genesis/.venv/bin/activate
$ pip uninstall -y torch
$ pip install torch --index-url https://download.pytorch.org/whl/cu126
$ python -c "import torch; print(torch.cuda.is_available(), torch.cuda.get_device_name(0))"
```

That must print `True` and the card name. If it prints `False`, Genesis will fall back to CPU — fix the wheel / driver before continuing.

3. Install the NVIDIA GL / EGL libraries so the interactive viewer is not silently using Mesa:

```sh
$ sudo apt update
$ sudo apt install -y libnvidia-gl-525
$ ldconfig -p | grep EGL
```

You want `libEGL_nvidia.so.0`. If the window is extremely slow, see the [Genesis EGL notes](https://genesis-world.readthedocs.io/en/latest/user_guide/overview/installation.html).

4. Launch on the GPU:

```sh
$ python hero_genesis/scripts/genesis_engine.py \
    --vis --num-robots 20 --arena 0 --pattern circle --backend gpu --no-physics
```

`gpu` and `cuda` are the same on Linux. Confirm the log line `gs.init(backend=...)` shows the CUDA backend, not `gs.cpu`.

### 4. Docker with an NVIDIA GPU

Install Docker and the [NVIDIA Container Toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html), then:

```sh
$ nvidia-smi
$ docker run --rm --gpus all nvidia/cuda:12.6.0-base-ubuntu22.04 nvidia-smi
```

The second command must see the same GPU. Build the Genesis image with a **CUDA** PyTorch wheel (the default image is CPU):

```sh
$ cd hero_genesis
$ docker compose --profile gpu build \
    --build-arg TORCH_INDEX=https://download.pytorch.org/whl/cu126
$ xhost +local:docker
$ docker compose --profile gpu up
```

That starts the viewer with `--backend gpu`. Environment the container needs:

```
NVIDIA_VISIBLE_DEVICES=all
NVIDIA_DRIVER_CAPABILITIES=all
```

On **WSL2**, if the window is black, pass the WSL CUDA libs as in the [Genesis Docker note](https://genesis-world.readthedocs.io/en/latest/user_guide/overview/installation.html):

```sh
$ docker run --gpus all --rm \
    -e DISPLAY=$DISPLAY \
    -e NVIDIA_DRIVER_CAPABILITIES=all \
    -e LD_LIBRARY_PATH=/usr/lib/wsl/lib \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    hero_common:genesis \
    python /hero/hero_genesis/scripts/genesis_engine.py --vis --num-robots 20 --backend gpu --no-physics
```

CPU-only Docker (no NVIDIA toolkit):

```sh
$ cd hero_genesis
$ docker compose up --build
```

The image copies `hero_description` and `hero_gazebo` so the URDF and arenas resolve inside the container.

### 5. ROS 1 topics from Genesis

On a Noetic (or Melodic) workspace that already contains this repo:

```sh
$ cd ~/catkin_ws
$ catkin_make
$ source devel/setup.bash
$ roslaunch hero_genesis genesis_bringup.launch num_robots:=20 arena:=0 backend:=gpu
```

`backend:=cpu` if you have no NVIDIA card. `hero_genesis_node.py` then publishes `/hero_N/cmd_vel`, `odom`, `laser`, `imu`, `led`, and `encoder`. Drive with the same teleop as hardware:

```sh
$ roslaunch hero_bringup hero_teleop.launch id:=0
```
