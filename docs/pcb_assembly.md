---
layout: page
title: Solder the board
permalink: /pcb_assembly/
section: build
lead: SMD first, then through-hole. The tutorial times this at about 20 minutes of reading and 130 minutes of building. Figures are from the HeRo V2 Robot Build Tutorial (v1.0, 27 Sep 2025).
---

<p class="toc"><a href="#passives">Passives</a> · <a href="#ics">ICs</a> · <a href="#leds">LEDs</a> · <a href="#connectors">Connectors</a> · <a href="#ir">IR sensors</a> · <a href="#boost">5 V boost</a> · <a href="#checks">Checks</a></p>

Work current-limited (≤300 mA) until the smoke test. Treat the Li-Po as a live cell once it is connected.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image54.jpg' | relative_url }}" alt="Tools for PCB work"><figcaption>Bench tools.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image61.jpg' | relative_url }}" alt="Populated HeRo board"><figcaption>A finished board.</figcaption></figure>
</div>

## BOM on the board

- Passives: R0–R8 (4k7), R9 (0 Ω), R10 (18 Ω), R15 (0 Ω), C1–C2 (100 pF). R11 is not mounted.
- Indicators: LED0–LED1 (WS2812B 5050). Optional charger LEDs: STDBY green 0805, CHRG red 0805.
- ICs: IRLML2502 (SOT-23), CD4051 (SOIC-16), TP4056 (SOP-8, optional charger).
- Sensors: TCRT5000L ×8.
- Connectors: two JST-PH-2, 1×4 female (I²C/UART), four 1×3 male (E/M), two 1×16 female (ESP), slide switch.

<figure class="figure">
  <img src="{{ '/assets/img/build/image25.jpg' | relative_url }}" alt="Blank HeRo PCB">
  <figcaption>Blank HeRo v2 board. Order Gerbers from the previous step if you do not have one.</figcaption>
</figure>

## Soldering order (SMD → THT)

<p class="step-meta" id="passives">About 90 minutes on the iron</p>

**1. Small passives** — C0603 then R0805 (C1–C2; C3–C4 optional; R0–R10, R12–R15). Leave R11 empty.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image93.jpg' | relative_url }}" alt="SMD capacitors"><figcaption>Capacitors.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image71.jpg' | relative_url }}" alt="SMD resistors"><figcaption>Resistors.</figcaption></figure>
</div>

**2. ICs** — TP4056 if you want onboard charge, then CD4051, then IRLML2502. Pin-1 / orientation dot to the silkscreen. Inspect bridges.

<div class="figure-grid" id="ics">
  <figure class="figure"><img src="{{ '/assets/img/build/image14.jpg' | relative_url }}" alt="IC soldering"><figcaption>ICs on the board.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image76.jpg' | relative_url }}" alt="IC orientation"><figcaption>Match the pin-1 mark.</figcaption></figure>
</div>

**3. Addressable LEDs** — WS2812B, arrow DIN → DOUT, polarity to silk. Continuity-check the pads.

<div class="figure-grid" id="leds">
  <figure class="figure"><img src="{{ '/assets/img/build/image90.jpg' | relative_url }}" alt="WS2812B LEDs"><figcaption>WS2812B orientation.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image67.jpg' | relative_url }}" alt="Status LEDs"><figcaption>Optional STDBY / CHRG LEDs.</figcaption></figure>
</div>

**4. Connectors and switch** — JST-PH-2 ×2, I²C/UART header, encoder/motor headers, ESP sockets, slide switch.

<div class="figure-grid" id="connectors">
  <figure class="figure"><img src="{{ '/assets/img/build/image46.jpg' | relative_url }}" alt="Headers"><figcaption>Headers.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image97.jpg' | relative_url }}" alt="Switch and sockets"><figcaption>Switch and ESP sockets.</figcaption></figure>
</div>

**5. IR sensors** — eight TCRT5000L, same standoff, coplanar, gap aligned around the ring.

<div class="figure-grid" id="ir">
  <figure class="figure"><img src="{{ '/assets/img/build/image27.jpg' | relative_url }}" alt="TCRT5000 sensors"><figcaption>TCRT5000 ring.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image108.jpg' | relative_url }}" alt="IR alignment"><figcaption>Keep them coplanar.</figcaption></figure>
</div>

## Tune the MT3608 to 5.0 V {#boost}

The paper uses an MT3608 step-up so the 3.7 V pack becomes a 5 V rail (motors included).

1. PSU + → VIN+, PSU GND → VIN−. Meter on VOUT+/VOUT−.
2. Set the bench supply to 4.0 V, current limit 0.30 A.
3. Turn the trimpot slowly toward 5.00 V. Do not overshoot.
4. Recheck under a short dummy load: 100 Ω (~50 mA), then 6.2 Ω (~0.8 A) or 5 Ω (~1.0 A) in bursts.
5. Power off. Mark the module “5 V”.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image22.jpg' | relative_url }}" alt="MT3608 wiring"><figcaption>Boost module on the bench.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image42.jpg' | relative_url }}" alt="Measuring 5 V"><figcaption>Trim to 5.00 V.</figcaption></figure>
</div>

## Electrical checks {#checks}

Unpowered: GND continuity; 0 Ω jumpers R9/R15; no 5 V↔GND or 3V3↔GND shorts.

Powered (bench or battery): 5.0 V / 0.3 A limit, switch on, watch quiescent current. Nothing should run hot.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image49.jpg' | relative_url }}" alt="Power-up check"><figcaption>First power-up.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image75.jpg' | relative_url }}" alt="Current-limited supply"><figcaption>Stay current-limited.</figcaption></figure>
</div>

Drive the WS2812B with a blink or rainbow. Confirm I²C pull-ups (~4.7 kΩ to 3V3) and an MPU6050 ACK if the e-hat is fitted. Walk the CD4051 channels; IR voltages should move with a white/black card.

<div class="figure-grid">
  <figure class="figure"><img src="{{ '/assets/img/build/image66.jpg' | relative_url }}" alt="LED test"><figcaption>LED bring-up.</figcaption></figure>
  <figure class="figure"><img src="{{ '/assets/img/build/image9.jpg' | relative_url }}" alt="IR channel test"><figcaption>IR / mux check.</figcaption></figure>
</div>

Optional smoke test: flash the stock firmware over USB (battery disconnected) and watch the serial boot at 115200.

<p><a class="btn btn-primary" href="{{ '/printing/' | relative_url }}">Next: print the body</a></p>
