---
layout: page
title: Print the body
permalink: /printing/
section: build
lead: PLA, 0.20 mm layers, 0.4 mm nozzle. Gears print cleaner with a finer nozzle. CAD on A360.
---

<div class="part-grid">
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/chassis_a.stl' | relative_url }}"></div>
    <h3>Chassis A</h3>
    <p>Motors and wheel shafts · 20% infill · support</p>
    <a href="{{ '/assets/models/chassis_a.stl' | relative_url }}" download>Download chassis_a.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/chasis_b.stl' | relative_url }}"></div>
    <h3>Chassis B</h3>
    <p>Board, encoders, battery · 20% infill · no support</p>
    <a href="{{ '/assets/models/chasis_b.stl' | relative_url }}" download>Download chasis_b.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/wheel.stl' | relative_url }}"></div>
    <h3>Wheel ×2</h3>
    <p>623ZZ press-fit · 20% infill · support</p>
    <a href="{{ '/assets/models/wheel.stl' | relative_url }}" download>Download wheel.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/castor_wheel.stl' | relative_url }}"></div>
    <h3>Castor ×2</h3>
    <p>4 mm ball · 100% infill · no support</p>
    <a href="{{ '/assets/models/castor_wheel.stl' | relative_url }}" download>Download castor_wheel.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/motor_gear.stl' | relative_url }}"></div>
    <h3>Motor gear ×2</h3>
    <p>1:1 to the wheel · 100% infill · no support</p>
    <a href="{{ '/assets/models/motor_gear.stl' | relative_url }}" download>Download motor_gear.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/motor_shaft.stl' | relative_url }}"></div>
    <h3>Motor shaft ×2</h3>
    <p>Wheel axle sleeve · 100% infill · no support</p>
    <a href="{{ '/assets/models/motor_shaft.stl' | relative_url }}" download>Download motor_shaft.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/encoder_shaft.stl' | relative_url }}"></div>
    <h3>Encoder shaft ×2</h3>
    <p>1:6 to the wheel · 100% infill · no support</p>
    <a href="{{ '/assets/models/encoder_shaft.stl' | relative_url }}" download>Download encoder_shaft.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/cover.stl' | relative_url }}"></div>
    <h3>Cover</h3>
    <p>20% infill · support</p>
    <a href="{{ '/assets/models/cover.stl' | relative_url }}" download>Download cover.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/cover_usb.stl' | relative_url }}"></div>
    <h3>USB slider</h3>
    <p>Door for the USB port</p>
    <a href="{{ '/assets/models/cover_usb.stl' | relative_url }}" download>Download cover_usb.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/ehat.stl' | relative_url }}"></div>
    <h3>E-hat</h3>
    <p>20% infill · no support</p>
    <a href="{{ '/assets/models/ehat.stl' | relative_url }}" download>Download ehat.stl</a>
  </article>
  <article class="part-card">
    <div class="stl-stage" data-stl="{{ '/assets/models/ehat_glove.stl' | relative_url }}"></div>
    <h3>E-hat glove</h3>
    <p>100% infill · no support</p>
    <a href="{{ '/assets/models/ehat_glove.stl' | relative_url }}" download>Download ehat_glove.stl</a>
  </article>
</div>

## Print settings

| | |
|---|---|
| Printer in the notes | Anet A8 |
| Nozzle | 0.4 mm |
| Filament | PLA |
| Slicer | Cura 4.8 |
| Default layer height | 0.20 mm |

Print the encoder-height shim at 0.10 mm, in 0.1–0.4 mm thicknesses, and keep the one that meshes cleanly.

[Fusion / A360](https://a360.co/3lWHiv0) · [all STLs on GitHub](https://github.com/verlab/hero_common/tree/master/hero_resources/3d_parts)

<p><a class="btn btn-primary" href="{{ '/assembly/' | relative_url }}">Next: assemble the robot</a></p>

<script type="module" src="{{ '/assets/js/stl-viewer.js' | relative_url }}"></script>
