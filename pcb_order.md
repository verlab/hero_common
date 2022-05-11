---
layout: page
title: PCB Order
permalink: /pcb_order/
---
<style>
* {
  box-sizing: border-box;
}

.column {
  float: left;
  width: 33.33%;
  padding: 5px;
}

/* Clearfix (clear floats) */
.row::after {
  content: "";
  clear: both;
  display: table;
}
</style>

<h3>How to request a PCB manufacturing service?</h3>

<p align="justify">Today it is extremely easy and affordable to prototype PCBs. The following is a tutorial on how you can request a PCB manufacturing service.</p>

<p align="justify">After designing the robot's PCB, we requested the services of the <a href="https://jlcpcb.com" target="_blank" rel="noopener noreferrer">JLCPCB company</a>, as it is good in quality and low cost. 
  Of course, other companies are just as good, so feel free to choose.</p>
  
<p align="justify">About the color of the PCB, we opted for the white color because it improves the brightness performance of the LEDs, but there are no restrictions on this.</p>
  
<p align="justify">Although we used some SMD components, we had no difficulty using the soldering iron to solder them. That way, a stencil board was not required.</p>

<p align="justify">To start an order, simply download the <a href="https://github.com/verlab/hero_common/blob/nodemcu/hero_resources/schematic/EAGLE/projects/hero_v2.6/board_2022-04-20.zip" target="_blank" rel="noopener noreferrer">Gerber File</a>, and send it to the PCB manufacturing service of your choice. Just pay attention to these requirements:</p>

 <ul class="fa-ul" style="list-style: none;">
  <li> Finished Copper >= 1 oz</li>
  <li> Min Hole Size: 0.3mm</li>
  <li> Min Track/Spacing: 6/6mil</li>
 </ul>
 
 <h4>PCB view</h4>
 <div class="row">
  <div class="column">
    <img src="https://user-images.githubusercontent.com/14208261/167929288-c28a8c2d-f3f0-4023-b38a-1e36fa129a3e.svg" alt="Image" width="350">
  </div>
  <div class="column">
    <img src="https://user-images.githubusercontent.com/14208261/167929288-c28a8c2d-f3f0-4023-b38a-1e36fa129a3e.svg" alt="Image" width="350">
  </div>
</div>

<p align="justify">Here is an exemple using the JLCPCB manufacturing service.</p>

<p align="center"><img src="https://user-images.githubusercontent.com/14208261/167928212-f264abf8-bd7c-41f0-a239-05c4a3284ae5.gif" alt="Image" width="600"></p>


<p align="justify">After a few days we receive the PCBs and we can start assembling the components.</p>
<p align="center"><img src="https://user-images.githubusercontent.com/14208261/167909052-f92410ec-06e9-4d90-a296-35aeae01de86.png" alt="Image" width="600"></p>

