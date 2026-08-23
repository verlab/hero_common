---
layout: page
title: Simulate in Gazebo
permalink: /robot_simulation/
section: software
lead: Step 4 of 4. Gazebo ships a differential-drive HeRo with odometry, IMU, and IR ranges (modeled as a laser). A small wizard drops an arena and a swarm, then writes a launch file.
---

You can run this step without a physical robot. The topics use the same `/hero_N` namespace.

## 1. Place an arena and a swarm

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

## 2. Replay the scene

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
