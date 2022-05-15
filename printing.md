



After making the [[robot's mainboard|PCB-Assembly]], we started making its chassis. At this stage, it is also necessary to buy some parts and next we provide a list. In addition, it is necessary to have access to a 3D printer or some service.

> **The mechanical design is open-source and was developed using [Autodesk F360](https://www.autodesk.com/products/fusion-360) software.**: If you want to extend/modify it, the project is available [here](https://a360.co/36zKPdi).

In the end, it is expected to get the robot as in the image below.
![hero_view](https://user-images.githubusercontent.com/14208261/164281570-9db151b4-c538-479a-b654-469616ad4e62.png)

# What components do I need to buy?
- 2 rubber rings 50mm;
- 2 M3x20mm bolt with nut and pressure washer;
- 16 M2.5x10mm screws self-tapping;
- 2 mouse rotary encoder >= 48 pulse;
- 2 bearings 623zz 3x10x4
- 2 steel balls 4mm diameter;

# What parts do I need to print?
The robot's chassis and some mechanical parts are made using additive manufacturing (3D printer). Mechanical parts like gears need to be printed in good quality, and maybe some minor adjustments (using sandpaper) are required. 

We use PLA/ABS because they are inexpensive, but other types can be used/tested. The required quality for printing is at least 200 microns.

The robot is composed of 16 parts, which preferably must be printed separately.

The files for printing (stl format) are available [here](https://github.com/verlab/hero_common/tree/nodemcu/hero_resources/3d_parts). If you want to modify or extend any part, I suggest using the CAD available [here](https://github.com/verlab/hero_common/tree/nodemcu/hero_resources/cad).

Below is a description of each part. 
- [castor_wheel.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/castor_wheel.stl): Screw-on castor wheel for robot balance adjustment.
- [chasis_b.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/chasis_b.stl): Chassis that supports the mainboard and encoders;
- [chassis_a.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/chassis_a.stl): Chassis that supports the motors and wheels;
- [cover.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/cover.stl): Dust protection cover;
- [cover_usb.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/cover_usb.stl): Sliding part for access to the USB connector;
- [ehat.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/ehat.stl): e-hat component to enclose mainboard expansions;
- [ehat_glove.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/ehat_glove.stl): Adapters for e-hat component;
- [encoder_shaft.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/encoder_shaft.stl): Spur gear/shaft encoder for wheel-encoder transmission;
- [motor_gear.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/motor_gear.stl): Coupled to the servo motor shaft and acts directly on the wheel;
- [motor_shaft.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/motor_shaft.stl): Wheel shaft supports the connection of the wheel to the chassis;
- [wheel.stl](https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/3d_parts/wheel.stl): Wheel spur geared;


# How to assemble the robot? (coming soon)
