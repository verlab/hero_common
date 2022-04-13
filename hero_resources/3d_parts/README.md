# 3D Printer Instructions

The parts that make up the robot were designed so that they can be printed by any conventional 3D printer. Some parts require a little more care when printing to avoid small warps, which may impact the robot's mechanics. Therefore, I recommend configuring your printer so that it can print the following parts in the following settings.


**NOTE**: Although getting good results when printing small parts (such as gears) using a 0.4m nozzle. I recommend, if possible, using a thinner nozzle to achieve even more satisfactory results.


## 3D Printer Setup
```
3D Printer: AnetA8
Nozzle: 0.4 mm
Filament: PLA
Slicer: Ultimaker Cura v4.8.0
```

## Parts
### AA8_chassis_a.gcode  
```
Profile: 0.20
Infill: 20%
Support: Yes
```      
### AA8_chasis_b.gcode
```
Profile: 0.20
Infill: 20%
Support: No
```    
### AA8_wheel.gcode
```
Profile: 0.20
Infill: 20%
Support: Yes
```
### AA8_castor_wheel.gcode     
```
Profile: 0.20
Infill: 100%
Support: No
```
### AA8_motor_gear.gcode
```
Profile: 0.20
Infill: 100%
Support: No
```
### AA8_motor_glove.gcode
```
Profile: 0.20
Infill: 100%
Support: No
```
### AA8_encoder_gear.gcode
```
Profile: 0.20
Infill: 100%
Support: No
```
### AA8_chasis_b_adjust.gcode  
**NOTE**: This is a tweaking piece. Its purpose is to adjust the height of the gear encoder in relation to the wheel gear. Print this part at different heights, for example (0.1, 0.2, 0.3, 0.4 mm) and test which provides the best fit between the gear encoder and the wheel.
```
Profile: 0.10
Infill: 100%
Support: No
```
### AA8_cover.gcode
```
Profile: 0.20
Infill: 20%
Support: Yes
```
### AA8_ehat.gcode          
```
Profile: 0.20
Infill: 20%
Support: No
```
### AA8_ehat_glove.gcode  
```
Profile: 0.20
Infill: 100%
Support: No
```  