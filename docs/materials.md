---
layout: page
title: Parts and cost
permalink: /materials/
section: build
lead: 18.72 USD in parts (Rezeck et al., Autonomous Robots, 2023). Retail, one-off buys at the time of the paper.
---

<p class="step-meta">Tutorial v1.0 · 27 Sep 2025 · Paulo Rezeck</p>

## Specifications (paper)

| Specification | Value |
|---|---|
| Size (L × W × H) | 0.068 × 0.073 × 0.076 m |
| Weight | 0.156 kg |
| Wheel distance | 0.0631 m |
| Wheel diameter | 0.0492 m |
| Linear speed | 0.25 m/s |
| Inertia | Ixx = Iyy = 1.27×10⁻⁴ kg·m², Izz = 1.04×10⁻⁴ kg·m² |
| Battery | 3.7 V, 1800 mAh Li-Po |
| Autonomy | up to 3 hours with all components in continuous use |
| MCU | ESP8266, 32-bit 160 MHz, 4 MB, Wi-Fi 802.11 |
| IR ring | 8 × TCRT5000, 45°, pulsed over-current, range up to 20 cm |
| Encoder | Kailh / mouse rotary, 48 PPR; 1:6 wheel–encoder gear → 1.25° / 0.54 mm per step |
| Motors | 2 × SG90 continuous servos, 1.8 kgf·cm |

<figure class="figure">
  <img src="{{ '/assets/img/build/hero_views.jpg' | relative_url }}" alt="HeRo from top, bottom, front, and side">
  <figcaption>HeRo 2.0, from the 2023 Autonomous Robots paper (Fig. “Top, bottom, front, and left views”).</figcaption>
</figure>

## Cost per robot (paper)

| Parts | Qty | Cost (USD) |
|---|---:|---:|
| Servo motors SG-90 | 2 | 2.06 |
| Mouse encoder 48 PPR | 2 | 0.10 |
| ESP8266 NodeMCU | 1 | 2.50 |
| Rubber O-ring 38 mm | 2 | 0.10 |
| IR TCRT5000 | 8 | 0.68 |
| LED RGB WS2812b | 2 | 0.51 |
| IMU MPU6050 | 1 | 0.85 |
| Li-Po 3.7 V 1800 mAh | 1 | 5.85 |
| PCB board and components | 1 | 4.30 |
| 3D-printed PLA parts and fasteners | 1 | 1.50 |
| **Total** |  | **18.72** |

## What to buy (assembly checklist)

From the build tutorial (September 2025). Use this on the bench; the paper table above is the cost reference.

**Drive and locomotion**
- SG90 continuous-rotation servos ×2 (green-label variant recommended), with horns and screws
- O-ring tires ×2
- 623ZZ bearings ×2
- Steel balls 4 mm ×2 (casters)
- M2.5 self-tapping screws plus assorted M3 screws, nuts, and washers

**Electronics**
- Blank HeRo v2 PCB (see [Order the PCB]({{ '/pcb_order/' | relative_url }}))
- ESP8266 / NodeMCU
- Li-Po 103450 (1S, 3.7 V 1800 mAh)
- MPU6050 IMU (optional e-hat)
- Two mouse-style quadrature encoders
- Passives and ICs listed on the [solder page]({{ '/pcb_assembly/' | relative_url }})

**Print set** — chassis A/B, wheels, casters, cover, USB slider, e-hat, gloves, motor gears, motor shafts, encoder shafts. See [Print the body]({{ '/printing/' | relative_url }}).

A printable spreadsheet is still in the repo: [assembly_materials.pdf](https://github.com/verlab/hero_common/raw/master/hero_resources/assembly_materials.pdf).

## Tools

Phillips and flat-head screwdrivers, needle-nose pliers, diagonal cutters, wire strippers, precision knife, fine-tip soldering iron, flux, desoldering braid, multimeter, ESD tweezers, safety glasses, isopropyl alcohol. Optional: current-limited bench PSU, hot-air station, PCB vise.

<p><a class="btn btn-primary" href="{{ '/pcb_order/' | relative_url }}">Next: order the PCB</a></p>
