---
layout: page
title: Assemble the robot
permalink: /assembly/
section: build
lead: About 45 minutes of reading and 110 minutes of building (tutorial v1.0, 27 Sep 2025). Figures are from that tutorial. Geometry and encoder ratios are from Rezeck et al., Auton. Robot (2023).
---

<p class="toc"><a href="#casters">Casters</a> · <a href="#motors">Motors</a> · <a href="#wheels">Wheels</a> · <a href="#battery">Battery</a> · <a href="#encoders">Encoders</a> · <a href="#board">Board</a> · <a href="#ehat">E-hat</a> · <a href="#trouble">Troubleshooting</a></p>

[PDF of the same tutorial]({{ '/assembly/Hero V2 Robot Build Tutorial-compressed.pdf' | relative_url }})

## Casters {#casters}

Take a printed caster shell, drop in a 4 mm steel ball, and crimp the rim with pliers so the ball stays in but still turns. Screw both casters to Chassis A. Set the height so the chassis sits level.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image21.jpg' | relative_url }}" alt="Inserting the caster ball"><figcaption>Ball in the cup.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image35.jpg' | relative_url }}" alt="Crimping the caster"><figcaption>Crimp just enough.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image37.jpg' | relative_url }}" alt="Casters on chassis A"><figcaption>On Chassis A.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image4.jpg' | relative_url }}" alt="Height adjustment"><figcaption>Adjust clearance.</figcaption></figure>
</div>

## Motors {#motors}

Prefer SG90 units already converted to continuous rotation. The tutorial recommends the **green-label** variant (no resistor swap). Stock angular servos need a CR modification first; after that, command ~1500 µs to center.

<figure class="figure">
  <img src="{{ '/assets/img/build/image73.jpg' | relative_url }}" alt="SG90 continuous servo">
  <figcaption>SG90 ready for the printed gear.</figcaption>
</figure>

**Gear adapter**

1. Pick a stock horn that fits the printed motor gear. Cut it down to the cylindrical hub. Wear glasses — chips fly.
2. Trim the hub until it press-fits the gear. A small drop of cyanoacrylate at the interface; keep glue off the teeth.
3. If the servo shaft sticks out, shorten it ~1.00–1.20 mm, cut flat.
4. Fasten with the original horn screw. Do not overtighten — friction kills the mesh.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image101.jpg' | relative_url }}" alt="Cutting the horn"><figcaption>Cut the horn to a hub.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image7.jpg' | relative_url }}" alt="Horn hub"><figcaption>Hub only.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image83.jpg' | relative_url }}" alt="Hub in gear"><figcaption>Press-fit, then glue.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image33.jpg' | relative_url }}" alt="Glued gear"><figcaption>Keep glue off the teeth.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image91.jpg' | relative_url }}" alt="Shortening the shaft"><figcaption>Shorten the shaft if needed.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image6.jpg' | relative_url }}" alt="Horn screw"><figcaption>Original horn screw.</figcaption></figure>
</div>

Mount each servo on Chassis A. Align both outputs at the stop pulse (1500 µs). Leave the mount screws slightly loose so the 1:1 gear train can sit. Trim motor cables to about 10 cm.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image63.jpg' | relative_url }}" alt="Servo on chassis"><figcaption>Servo in the printed mount.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image41.jpg' | relative_url }}" alt="Both motors installed"><figcaption>Both sides aligned.</figcaption></figure>
</div>

The paper’s drivetrain is a **1:1 motor–wheel gear** plus a **1:6 wheel–encoder gear**. Combined with the 48 PPR mouse encoder that is a **1.25° / 0.54 mm** wheel step.

## Wheels {#wheels}

Press a 623ZZ into each printed hub (vise or a flat spacer — do not hammer the bearing). Seat the O-ring. Fit the printed shaft sleeve so the wheel turns with almost no backlash and no wobble.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image105.jpg' | relative_url }}" alt="Wheel parts"><figcaption>Wheel kit.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image69.jpg' | relative_url }}" alt="Pressing the bearing"><figcaption>Press the 623ZZ.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image10.jpg' | relative_url }}" alt="O-ring tire"><figcaption>O-ring on the rim.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image17.jpg' | relative_url }}" alt="Finished wheel"><figcaption>Ready to mesh.</figcaption></figure>
</div>

Install the wheel on the motor gear. The mesh should be smooth. A tiny drop of glue on the support screw into Chassis A keeps it from backing out.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image57.jpg' | relative_url }}" alt="Wheel on shaft"><figcaption>Wheel on the axle.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image12.jpg' | relative_url }}" alt="Gear mesh"><figcaption>Motor gear to wheel.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image5.jpg' | relative_url }}" alt="Support screw"><figcaption>Support screw.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image30.jpg' | relative_url }}" alt="Both wheels"><figcaption>Check for wobble.</figcaption></figure>
</div>

## Battery and Chassis B {#battery}

Seat the 1S Li-Po (paper: 3.7 V, 1800 mAh) in the cradle between A and B. Chassis B is labeled **USB** and **Front**: battery cable through USB, motor cables through Front.

<div class="callout warn">A cover screw that is too long can pierce the pack. Check length before you tighten the top shell.</div>

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image34.jpg' | relative_url }}" alt="Battery in cradle"><figcaption>Battery in the cradle.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image107.jpg' | relative_url }}" alt="Cable routing"><figcaption>USB vs Front holes.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image24.jpg' | relative_url }}" alt="Stacking chassis B"><figcaption>Stack B on A.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image38.jpg' | relative_url }}" alt="Four screws"><figcaption>Four screws.</figcaption></figure>
</div>

## Encoders {#encoders}

Mouse-style quadrature encoders. Remove the detent spring so the shaft is smooth. Solder a JST-PH header. Cut shafts to length; wear glasses.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image29.jpg' | relative_url }}" alt="Encoder spring"><figcaption>Drop the detent spring.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image26.jpg' | relative_url }}" alt="Encoder wiring"><figcaption>JST-PH on the pins.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image92.jpg' | relative_url }}" alt="Encoder in chassis B"><figcaption>Pocket in Chassis B.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image20.jpg' | relative_url }}" alt="Encoder gear mesh"><figcaption>Gear to the wheel. Sand if it binds.</figcaption></figure>
</div>

## Board, cover, wiring {#board}

Mount the populated PCB on Chassis B. Fit the cover with eight screws — moderate torque. Then put the wheels on for the final motor → wheel → encoder check.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image110.jpg' | relative_url }}" alt="Board on chassis B"><figcaption>Board on B.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image45.jpg' | relative_url }}" alt="ESP seated"><figcaption>ESP / NodeMCU seated.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image32.jpg' | relative_url }}" alt="Cover"><figcaption>Cover.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image28.jpg' | relative_url }}" alt="Cover screws"><figcaption>Eight screws, clear of the pack.</figcaption></figure>
</div>

Servo leads: signal to PWM, red to 5 V, brown/black to GND. Battery JST last. Never reverse the pack.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image59.jpg' | relative_url }}" alt="Servo plugs"><figcaption>Servo plugs.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image70.jpg' | relative_url }}" alt="Battery JST"><figcaption>Battery JST.</figcaption></figure>
</div>

## E-hat {#ehat}

The paper’s e-hat is a 4-pin I²C/UART bus with 5 V at 800 mA. Solder male headers on the MPU6050, screw it into the printed hat, and plug the hat onto the I²C connector.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image16.jpg' | relative_url }}" alt="IMU headers"><figcaption>IMU headers.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image84.jpg' | relative_url }}" alt="IMU in e-hat"><figcaption>IMU in the hat.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image106.jpg' | relative_url }}" alt="E-hat on the robot"><figcaption>Hat on the I²C bus.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image51.jpg' | relative_url }}" alt="Finished robot"><figcaption>Mechanical check: free wheels, casters, no cable rub.</figcaption></figure>
</div>

## Troubleshooting {#trouble}

| Symptom | What the tutorial says to check |
|---|---|
| Motors dead or weak | PWM–5 V–GND order; boost still 5 V under load; pack &gt; 3.6 V |
| Wheel wobble / backlash | Hub seating, bearings fully in, sand or shim the gear adapter |
| Encoder drops counts | Detent fully gone, JST joints, no lateral shaft play |
| IR silent | Sensor orientation, LED polarity, current-limit resistors |
| Board off | MT3608 at 5.0 V, JST polarity, switch solder |
| Boost hot | Stay ≤ 0.8 A continuous or add a heatsink |

Next: [flash firmware]({{ '/firmware/' | relative_url }}), [join ROS]({{ '/ros/' | relative_url }}), then [calibrate]({{ '/calibration/' | relative_url }}).
