---
layout: home
title: Home
---

<section class="hero wrap">
  <p class="kicker">VeRLab · Universidade Federal de Minas Gerais</p>
  <h1>A swarm robot you can print, solder, and drive in ROS.</h1>
  <p class="lede">HeRo is a small differential-drive platform for research and teaching. The body is 3D-printed, the board is open, and every robot speaks ROS 1 over Wi‑Fi — so a classroom set behaves like a real multi-robot system, not a toy.</p>
  <div class="actions">
    <a class="btn btn-primary" href="{{ '/materials/' | relative_url }}">Build a robot</a>
    <a class="btn btn-ghost" href="{{ '/robot_simulation/' | relative_url }}">Run the simulator</a>
    <a class="btn btn-ghost" href="https://github.com/verlab/hero_common">View the source</a>
  </div>
  <div class="stats">
    <div class="stat"><b>18.72&nbsp;USD</b><span>parts, 2023 paper, retail</span></div>
    <div class="stat"><b>≤3&nbsp;h</b><span>1800&nbsp;mAh, all systems on</span></div>
    <div class="stat"><b>8 IR</b><span>proximity sensors, 20&nbsp;cm</span></div>
    <div class="stat"><b>ROS 1</b><span>rosserial over TCP</span></div>
  </div>
  <div class="media-frame">
    <iframe src="https://www.youtube.com/embed/JQvuYeF24lY" title="HeRo swarm platform" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
  </div>
</section>

<section class="section wrap">
  <h2>From empty table to swarm</h2>
  <p class="section-lead">You do not need a machine shop. Order the PCB, print the chassis, flash the ESP8266, and join the robots on a 2.4&nbsp;GHz network.</p>
  <div class="cards">
    <article class="card">
      <h3>1. Build</h3>
      <p>Buy the BOM, fabricate the latest board, print the body, and assemble the drivetrain. A printable tutorial walks through wheels, motors, and the e-hat.</p>
      <a href="{{ '/assembly/' | relative_url }}">Assembly guide →</a>
    </article>
    <article class="card">
      <h3>2. Flash</h3>
      <p>The firmware runs on an ESP8266. Cover the IR ring at boot to open the web configurator and set the robot id, Wi‑Fi, and ROS master.</p>
      <a href="{{ '/firmware/' | relative_url }}">Firmware notes →</a>
    </article>
    <article class="card">
      <h3>3. Command</h3>
      <p>Each robot appears as <code>/hero_N</code>. Drive with <code>cmd_vel</code>, read odom and the IR scan, or spawn a swarm in Gazebo first.</p>
      <a href="{{ '/ros/' | relative_url }}">ROS interface →</a>
    </article>
  </div>
</section>

<section class="section wrap">
  <h2>What is on the robot</h2>
  <p class="section-lead">Sensors and actuators that matter for swarm experiments, without a custom ASIC or a $400 chassis.</p>
  <div class="features">
    <div class="feature"><strong>Wheel odometry</strong><span>Quadrature encoders, 288 steps/rev, onboard PID speed control.</span></div>
    <div class="feature"><strong>IR proximity ring</strong><span>Eight long-range sensors published as a LaserScan.</span></div>
    <div class="feature"><strong>Optional IMU</strong><span>MPU6050 on I2C; off by default to save cycles.</span></div>
    <div class="feature"><strong>Addressable LEDs</strong><span>WS2812 ring for status, IDs, and experiment cues.</span></div>
    <div class="feature"><strong>Onboard charging</strong><span>TP4056 path on recent PCB revisions.</span></div>
    <div class="feature"><strong>Expansion bus</strong><span>I2C, serial, and GPIO on the top hat.</span></div>
    <div class="feature"><strong>Wi‑Fi + TCP</strong><span>rosserial to the ROS master; no USB tether.</span></div>
    <div class="feature"><strong>Gazebo twin</strong><span>Same namespace and sensors, plus a swarm wizard.</span></div>
    <div class="feature"><strong>Open hardware</strong><span>EAGLE schematics, STL files, and ROS packages in one repo.</span></div>
  </div>
</section>

<section class="section wrap">
  <h2>Seen in the wild</h2>
  <p class="section-lead">HeRo 2.0 was written up on Wevolver and used for odometry, flocking, coverage, and cooperative transport experiments.</p>
  <div class="actions">
    <a class="btn btn-ghost" href="https://www.wevolver.com/article/hero-20-an-ultra-low-cost-3d-printed-robotics-platform-could-open-swarm-robotics-experimentation-up-to-all">Wevolver feature</a>
    <a class="btn btn-ghost" href="{{ '/news/' | relative_url }}">Watch experiments</a>
    <a class="btn btn-ghost" href="{{ '/publications/' | relative_url }}">Read the papers</a>
  </div>
</section>
