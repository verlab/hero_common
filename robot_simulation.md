---
layout: page
title: Robot Simulation
permalink: /robot_simulation/
---

HeRo is simulated into Gazebo simulator.

## HeRo Wizard
We create a high-level UI interface that should help others to instantiate a gazebo environment.
Its is a simple wizard software that help select an environment and the robots. 
After selecting, and commit the object, they should appear on gazebo were we can drag them and place them wherever we want.
Finally, generate a launch file that compile this setup.

To create a environment, use this launch file:
```sh
$ roslaunch hero_gazebo gazebo_wizard.launch
```
It will open gazebo and this UI interface:

![system](https://github.com/verlab/hero_common/blob/master/hero_resources/media/images/gazebo_wizard1.png)))

### Steps:

1. Select the arena in the list (see figure);
2. By clicking on commit arena button, the object will be instantiate on gazebo. Clear arena button should remove it.
3. Select the number of robots.
4. Select the sensors available for the robots.
5. By clicking on commit swarm button, the robots will be instantiate on gazebo. Clear swarm will remove them.
6. By using gazebo simulator, make adjustments on the scene, and using the Generate Launch File button will compile the scene in a launch file for future uses.

![system](https://github.com/verlab/hero_common/blob/master/hero_resources/media/images/gazebo_wizard2.png))

Once you have properly setup your arena on Gazebo, close Gazebo sim and HeRo wizard window.

## How to use
Now, let start it again but without need for pre-set environment on HeRo wizard.

First, start Gazebo simular by running this command:
```sh
$ roslaunch hero_gazebo gazebo_bringup.launch 
```

Then, run this command to spawn the robots and the arena:
```sh
$ roslaunch hero_gazebo env_spawn.launch
```

Now you can start using the robots! Check the topics:
```sh
$ rostopic list
/clock
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/performance_metrics
/gazebo/set_link_state
/gazebo/set_model_state
/hero_0/cmd_vel
/hero_0/laser
/hero_0/led
/hero_0/odom
/hero_1/cmd_vel
/hero_1/laser
/hero_1/led
/hero_1/odom
.
.
.
/joint_states
/rosout
/rosout_agg
/tf
/tf_static
```

![system](https://github.com/verlab/hero_common/blob/master/hero_resources/media/images/gazebo_wizard3.png)


## Features
- Differential drive controller
- Odometry
- IMU
- IR Proximity range (simulated with laser)
