/*
 * HERO web config — embedded HTML/CSS/JS (offline, no CDN).
 */
#include "web_config_embed.h"
#include <ESP8266WebServer.h>

static const char HTML_DOC[] PROGMEM = R"HEROHTML(<!DOCTYPE html>
<html lang="en"><head><meta charset="utf-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>HERO | Field configuration</title>
<style>
:root{--bg:#0c0e12;--surface:#141922;--card:#1a2130;--border:#2a3344;--text:#e6edf3;--muted:#8b9cb3;--accent:#00d4aa;--accent-dim:#00997a;--warn:#ffb020;--danger:#f85149;--shadow:0 4px 24px rgba(0,0,0,.45)}
*{box-sizing:border-box}body{margin:0;font-family:system-ui,-apple-system,"Segoe UI",Roboto,sans-serif;background:var(--bg);color:var(--text);min-height:100vh;letter-spacing:.01em}
header{padding:1rem 1.25rem;background:linear-gradient(180deg,var(--surface) 0%,var(--bg) 100%);border-bottom:1px solid var(--border);box-shadow:var(--shadow)}
header h1{margin:0;font-size:1.15rem;font-weight:600;letter-spacing:.06em;text-transform:uppercase;color:var(--accent)}
header p{margin:.4rem 0 0;font-size:.8rem;color:var(--muted);max-width:52rem}
.wrap{max-width:1080px;margin:0 auto;padding:1rem}
.tabs{display:flex;flex-wrap:wrap;gap:.25rem;margin:1rem 0;border-bottom:1px solid var(--border);padding-bottom:2px}
.tab{padding:.5rem .9rem;border:1px solid transparent;border-radius:6px 6px 0 0;background:transparent;color:var(--muted);cursor:pointer;font-size:.78rem;font-weight:500;letter-spacing:.04em;text-transform:uppercase}
.tab:hover{color:var(--text);background:var(--surface)}
.tab.on{background:var(--card);color:var(--accent);border-color:var(--border);border-bottom-color:var(--card);margin-bottom:-1px}
.panel{display:none;background:var(--card);border:1px solid var(--border);border-radius:0 8px 8px 8px;padding:1.15rem;box-shadow:var(--shadow);margin-bottom:1rem}
.panel.on{display:block}
.panel h2{margin:0 0 .75rem;font-size:.95rem;font-weight:600;color:var(--text);letter-spacing:.05em;text-transform:uppercase;border-left:3px solid var(--accent);padding-left:.6rem}
.panel h3{margin:1rem 0 .5rem;font-size:.8rem;color:var(--muted);text-transform:uppercase;letter-spacing:.06em}
label{display:block;font-size:.68rem;color:var(--muted);margin:.45rem 0 .2rem;text-transform:uppercase;letter-spacing:.05em}input,textarea{width:100%;padding:.5rem;border:1px solid var(--border);border-radius:6px;font-size:.9rem;background:var(--surface);color:var(--text)}
input:focus,textarea:focus{outline:none;border-color:var(--accent)}
.row{display:grid;grid-template-columns:1fr 1fr;gap:.75rem}@media(max-width:720px){.row{grid-template-columns:1fr}}
.btn{background:linear-gradient(180deg,var(--accent) 0%,var(--accent-dim) 100%);color:#061018;border:none;padding:.55rem 1rem;border-radius:6px;font-weight:600;cursor:pointer;margin:.25rem .35rem .25rem 0;font-size:.78rem;letter-spacing:.04em;text-transform:uppercase}
.btn:hover{filter:brightness(1.08)}.btn.warn{background:linear-gradient(180deg,#ffc44d,#d9a320);color:#1a1408}.btn.danger{background:linear-gradient(180deg,#f87168,#c9180f);color:#fff}
small.hint{color:var(--muted);font-size:.72rem;line-height:1.45;display:block;margin:.35rem 0 .75rem}
.grid2{display:grid;grid-template-columns:1fr 1fr;gap:1rem}@media(max-width:720px){.grid2{grid-template-columns:1fr}}
.motor-val{font-family:ui-monospace,monospace;font-size:1.05rem;color:var(--accent);font-weight:600}
canvas{width:100%;max-width:100%;border-radius:6px;background:var(--surface);border:1px solid var(--border)}
table.const{width:100%;font-size:.75rem;border-collapse:collapse;color:var(--text)}
table.const td,table.const th{border:1px solid var(--border);padding:.35rem .5rem;text-align:left}
table.const th{background:var(--surface);color:var(--muted);text-transform:uppercase;font-size:.68rem;letter-spacing:.04em}
.badge{display:inline-block;background:var(--surface);color:var(--accent);padding:.2rem .5rem;border-radius:4px;font-size:.68rem;margin-left:.35rem;border:1px solid var(--border);letter-spacing:.04em}
.ledrow{display:flex;flex-wrap:wrap;gap:.4rem;align-items:center}
code{font-size:.78em;background:var(--surface);padding:.1rem .35rem;border-radius:4px;border:1px solid var(--border)}
</style></head><body>
<header><div class="wrap"><h1>HERO · Field configuration</h1><p>Access point mode · offline · Wi‑Fi network <code>HERO_ROBOT_*</code> · PWM neutral is typically 1500 µs (below / above drives opposite directions).</p></div></header>
<div class="wrap">
<div class="tabs" id="tabs">
<button type="button" class="tab on" data-t="t1">Connection</button>
<button type="button" class="tab" data-t="t2">Motors (test)</button>
<button type="button" class="tab" data-t="t3">Motors (EEPROM)</button>
<button type="button" class="tab" data-t="t4">Encoders</button>
<button type="button" class="tab" data-t="t5">Proximity</button>
<button type="button" class="tab" data-t="t6">LEDs</button>
<button type="button" class="tab" data-t="t7">PID</button>
<button type="button" class="tab" data-t="t8">Firmware</button>
</div>
<section id="t1" class="panel on"><h2>Connection &amp; identity</h2>
<form id="fConn"><div class="row"><div><label>Robot ID</label><input name="robotId" id="robotId" type="number" min="0" max="999" required/></div>
<div><label>Description</label><input name="robotDescription" id="robotDescription" maxlength="19"/></div></div>
<div class="row"><div><label>Wi‑Fi SSID (STA)</label><input name="wificSSID" id="wificSSID" maxlength="19" required/></div>
<div><label>Wi‑Fi password</label><input name="wificPassword" id="wificPassword" maxlength="19" required/></div></div>
<label>ROS master (IP or hostname)</label><input name="rosMasterAddress" id="rosMasterAddress" maxlength="19" required/>
<p><button class="btn" type="submit">Save connection</button></p></form>
<p><span id="verInfo" class="badge">…</span></p>
</section>
<section id="t2" class="panel"><h2>Motor PWM test</h2>
<p class="hint">Servo PWM in microseconds (1000–2000). Output is <strong>slew‑limited</strong> in firmware toward the setpoint (see <em>Motors (EEPROM)</em> for rate). Command holds until <strong>Stop motors</strong>.</p>
<div class="grid2"><div><label>Left <span id="lv" class="motor-val">1500</span> µs</label><input type="range" id="sl" min="1000" max="2000" value="1500"/></div>
<div><label>Right <span id="rv" class="motor-val">1500</span> µs</label><input type="range" id="sr" min="1000" max="2000" value="1500"/></div></div>
<p><button class="btn" type="button" id="bApply">Apply PWM</button><button class="btn warn" type="button" id="bStop">Stop motors</button></p>
</section>
<section id="t3" class="panel"><h2>Motors — EEPROM</h2>
<p class="hint"><strong>Ramp rate</strong> limits how fast PWM can move toward the command (µs per second). Lower = softer start / less inrush. Stored with stop PWM (neutral) values.</p>
<form id="fMot"><div class="row"><div><label>Left stop PWM (µs)</label><input name="m_l" id="m_l" type="number" min="1000" max="2000" required/></div>
<div><label>Right stop PWM (µs)</label><input name="m_r" id="m_r" type="number" min="1000" max="2000" required/></div></div>
<div class="row"><div><label>Ramp rate (µs/s)</label><input name="m_ramp" id="m_ramp" type="number" min="100" max="8000" step="50" required/></div></div>
<p><button class="btn" type="submit">Save motors (EEPROM)</button></p></form>
</section>
<section id="t4" class="panel"><h2>Encoders</h2>
<p class="hint">Filtered wheel speeds from live telemetry (~5 Hz).</p>
<canvas id="c1" width="480" height="110"></canvas>
<h3>IMU snapshot</h3><pre id="imu" style="background:var(--surface);padding:.65rem;border-radius:6px;font-size:.72rem;border:1px solid var(--border);overflow:auto">—</pre>
</section>
<section id="t5" class="panel"><h2>Proximity (IR)</h2>
<p class="hint">Estimated range per channel (mm) using current calibration. Autocalib matches <code>hero_ir_calib.py</code>: 100 samples, mean intensity × d² → α, then written to EEPROM.</p>
<canvas id="cIrMm" width="480" height="140"></canvas>
<h3>Raw intensity (debug)</h3>
<canvas id="c2" width="480" height="90"></canvas>
<div class="row"><div><label>Autocalib standoff (mm)</label><input type="number" id="irDmm" value="100" min="20" max="500"/></div>
<div><label>Autocalib status</label><pre id="irCalibStatus" style="background:var(--surface);padding:.5rem;border-radius:6px;font-size:.72rem;margin:.5rem 0 0;border:1px solid var(--border)">—</pre></div></div>
<p><button class="btn" type="button" id="bIrStart">Start autocalib (100 samples)</button><button class="btn warn" type="button" id="bIrCancel">Cancel</button></p>
<form id="fIr"><h3>Calibration α (per channel)</h3><div class="row" id="laserIrRow"></div>
<p><button class="btn" type="submit">Save α to EEPROM</button></p></form>
</section>
<section id="t6" class="panel"><h2>WS2812 LEDs</h2>
<p class="hint">Local test pattern (no ROS). Default brightness max.</p>
<div class="ledrow">
<button class="btn" type="button" data-lr="255" data-lg="0" data-lb="0">Red</button>
<button class="btn" type="button" data-lr="0" data-lg="255" data-lb="0">Green</button>
<button class="btn" type="button" data-lr="0" data-lg="0" data-lb="255">Blue</button>
<button class="btn" type="button" data-lr="0" data-lg="200" data-lb="255">Cyan</button>
<button class="btn" type="button" data-lr="255" data-lg="0" data-lb="255">Magenta</button>
<button class="btn warn" type="button" data-lr="255" data-lg="200" data-lb="0">Amber</button>
<button class="btn" type="button" data-lr="255" data-lg="255" data-lb="255">White</button>
<button class="btn danger" type="button" id="bLedOff">Off</button>
</div></section>
<section id="t7" class="panel"><h2>PID — EEPROM</h2>
<form id="fPid"><h3>Velocity</h3><div class="row"><div><label>Kp L</label><input name="v_lkp" id="v_lkp" step="any"/></div><div><label>Ki L</label><input name="v_lki" id="v_lki" step="any"/></div></div>
<div class="row"><div><label>Kd L</label><input name="v_lkd" id="v_lkd" step="any"/></div><div><label>Kp R</label><input name="v_rkp" id="v_rkp" step="any"/></div></div>
<div class="row"><div><label>Ki R</label><input name="v_rki" id="v_rki" step="any"/></div><div><label>Kd R</label><input name="v_rkd" id="v_rkd" step="any"/></div></div>
<h3>Position</h3><div class="row"><div><label>Kp L</label><input name="p_lkp" id="p_lkp" step="any"/></div><div><label>Ki L</label><input name="p_lki" id="p_lki" step="any"/></div></div>
<div class="row"><div><label>Kd L</label><input name="p_lkd" id="p_lkd" step="any"/></div><div><label>Kp R</label><input name="p_rkp" id="p_rkp" step="any"/></div></div>
<div class="row"><div><label>Ki R</label><input name="p_rki" id="p_rki" step="any"/></div><div><label>Kd R</label><input name="p_rkd" id="p_rkd" step="any"/></div></div>
<p><button class="btn" type="submit">Save PID</button></p></form>
<p><button class="btn danger" type="button" id="bReset">Full EEPROM reset</button></p>
</section>
<section id="t8" class="panel"><h2>Compiled constants (<code>config.h</code>)</h2>
<p class="hint">Read‑only. Changing values requires rebuild and reflash.</p>
<div id="constBox">Loading…</div>
</section>
</div>
<script>
(function(){
var L=64,W1=document.getElementById('c1'),W2=document.getElementById('c2'),Wir=document.getElementById('cIrMm');
var g1=W1.getContext('2d'),g2=W2.getContext('2d'),gIr=Wir.getContext('2d');
var h1=[],h2=[];
function fit(C){C.width=C.parentElement.clientWidth||480}
function line(g,arr,col){var n=arr.length,w=g.canvas.width,h=g.canvas.height,pad=h*0.05,i,x;if(n<2)return;var mn=Math.min.apply(null,arr),mx=Math.max.apply(null,arr);if(mx-mn<1e-6){mn-=1;mx+=1}g.strokeStyle=col;g.beginPath();for(i=0;i<n;i++){x=i/(n-1)*w;var y=h-(arr[i]-mn)/(mx-mn)*h*0.9-pad;if(!i)g.moveTo(x,y);else g.lineTo(x,y)}g.stroke()}
function encBG(g){var w=g.canvas.width,h=g.canvas.height,i;g.clearRect(0,0,w,h);g.fillStyle='#141922';g.fillRect(0,0,w,h);g.strokeStyle='#2a3344';for(i=0;i<=4;i++){g.beginPath();g.moveTo(0,i*h/4);g.lineTo(w,i*h/4);g.stroke()}}
function encDraw(g,a1,a2,c1,c2){encBG(g);line(g,a1,c1);line(g,a2,c2)}
function irBarDraw(g,mm,maxMm){var w=g.canvas.width,h=g.canvas.height,n=8,i,v,bw=w/n*0.62,pad=(w/n-bw)/2,mx=maxMm||220;g.clearRect(0,0,w,h);g.fillStyle='#141922';g.fillRect(0,0,w,h);g.strokeStyle='#2a3344';for(i=0;i<=4;i++){g.beginPath();g.moveTo(0,i*h/5);g.lineTo(w,i*h/5);g.stroke()}for(i=0;i<n;i++){v=(mm&&mm[i])||0;if(v<0)v=0;if(v>mx)v=mx;var bh=(v/mx)*(h-28),x=i*(w/n)+pad,y=h-bh-18;g.fillStyle='#00d4aa';g.fillRect(x,y,bw,bh);g.fillStyle='#e6edf3';g.font='11px ui-monospace,monospace';g.fillText(String(i),x,y-3);g.fillText(Math.round(v)+' mm',x,Math.min(h-4,y+bh+12))}}
function ajax(u,m,d,cb){var x=new XMLHttpRequest();x.open(m||'GET',u,1);x.onreadystatechange=function(){if(x.readyState===4)cb(x.status,x.responseText)};if(d){x.setRequestHeader('Content-Type','application/x-www-form-urlencoded');x.send(d)}else x.send()}
function tabs(){var t=document.querySelectorAll('.tab'),p=document.querySelectorAll('.panel');t.forEach(function(b){b.onclick=function(){var id=b.getAttribute('data-t');t.forEach(function(x){x.classList.toggle('on',x===b)});p.forEach(function(x){x.classList.toggle('on',x.id===id)});if(id==='t8')loadConst()}})}
function loadConst(){ajax('/api/constants',0,0,function(st,tx){var b=document.getElementById('constBox');if(st!==200){b.textContent='Load failed';return}var o,j;try{o=JSON.parse(tx)}catch(e){b.textContent='Invalid JSON';return}
var k=Object.keys(o).sort(),html='<table class="const"><tr><th>Name</th><th>Value</th></tr>';k.forEach(function(key){j=o[key];if(typeof j==='object')j=JSON.stringify(j);html+='<tr><td>'+key+'</td><td>'+j+'</td></tr>'});html+='</table>';b.innerHTML=html})}
function poll(){ajax('/api/telemetry',0,0,function(st,tx){if(st!==200)return;var d;try{d=JSON.parse(tx)}catch(e){return}
document.getElementById('verInfo').textContent='FW '+d.versions.firmware+' · HW '+d.versions.hardware+' · CFG '+d.versions.config;
var v=d.enc||{};h1.push(v.vLf||0);h2.push(v.vRf||0);while(h1.length>L){h1.shift();h2.shift()}
fit(W1);fit(W2);fit(Wir);encDraw(g1,h1,h2,'#00d4aa','#ff8a65');encBG(g2);line(g2,(d.ir&&d.ir.i)||[],'#5c7cfa');irBarDraw(gIr,(d.irMm&&d.irMm.mm)||[],220);
document.getElementById('imu').textContent=JSON.stringify(d.imu||{},null,2)})}
function motorPost(l,r,stop){var q=stop?'stop=1':'l='+encodeURIComponent(l)+'&r='+encodeURIComponent(r);ajax('/api/motor','POST',q,function(){})}
function formToQuery(f){return[].map.call(f.elements,function(el){return el.name?encodeURIComponent(el.name)+'='+encodeURIComponent(el.value):''}).filter(Boolean).join('&')}
function saveConn(e){e.preventDefault();ajax('/saveParams','POST',formToQuery(e.target),function(st,tx){try{var j=JSON.parse(tx)}catch(x){alert('Invalid response');return}if(j.status==='success')location.reload();else alert('Save failed')})}
function saveMot(e){e.preventDefault();ajax('/saveHardware','POST',formToQuery(e.target),function(st,tx){try{var j=JSON.parse(tx)}catch(x){alert('Invalid response');return}if(j.status==='success')alert('Motors saved');else alert('Save failed')})}
function saveIr(e){e.preventDefault();ajax('/saveHardware','POST',formToQuery(e.target),function(st,tx){try{var j=JSON.parse(tx)}catch(x){alert('Invalid response');return}if(j.status==='success')alert('IR calibration saved');else alert('Save failed')})}
function savePid(e){e.preventDefault();ajax('/saveHardware','POST',formToQuery(e.target),function(st,tx){try{var j=JSON.parse(tx)}catch(x){alert('Invalid response');return}if(j.status==='success')alert('PID saved');else alert('Save failed')})}
function resetE(){ajax('/resetEEPROM','POST','',function(st,tx){try{var j=JSON.parse(tx)}catch(x){return}if(j.status==='success')location.reload();else alert('Reset failed')})}
function fillLaserIrRow(ir){var row=document.getElementById('laserIrRow');if(!row)return;if(!row.children.length){for(var ji=0;ji<8;ji++){var r=document.createElement('div');r.innerHTML='<label>IR '+ji+' α</label><input name="ir'+ji+'" id="ir'+ji+'" step="any"/>';row.appendChild(r)}}
for(var j=0;j<8;j++){var el=document.getElementById('ir'+j);if(el)el.value=(ir[j]!==undefined)?ir[j]:0.5}}
function fillForm(d){
document.getElementById('robotId').value=d.conn.robot_id;document.getElementById('robotDescription').value=d.conn.robot_desc||'';document.getElementById('wificSSID').value=d.conn.wifi_ssid||'';document.getElementById('wificPassword').value=d.conn.wifi_pass||'';document.getElementById('rosMasterAddress').value=d.conn.ros_master||'';
var pv=d.pidVel||{},p=d.pidPos||{},m=d.motor||{},ir=d.irAlpha||[];
['lkp','lki','lkd','rkp','rki','rkd'].forEach(function(k){var el=document.getElementById('v_'+k);if(el)el.value=pv[k]!==undefined&&pv[k]>=0?pv[k]:''});
['lkp','lki','lkd','rkp','rki','rkd'].forEach(function(k){var el=document.getElementById('p_'+k);if(el)el.value=p[k]!==undefined&&p[k]>=0?p[k]:''});
document.getElementById('m_l').value=m.left>=0?m.left:1500;document.getElementById('m_r').value=m.right>=0?m.right:1500;
var rp=document.getElementById('m_ramp');if(rp){var rv=(m.ramp_us_per_s!==undefined)?parseInt(m.ramp_us_per_s,10):2500;if(rv<100||rv>8000)rv=2500;rp.value=rv}
fillLaserIrRow(ir)}
var irPoll=null;
function pollIrCalib(){ajax('/api/ir_autocalib','GET',0,function(st,tx){if(st!==200)return;var o;try{o=JSON.parse(tx)}catch(e){return}
document.getElementById('irCalibStatus').textContent=JSON.stringify(o);
if(o.phase===2&&o.alpha){for(var i=0;i<8;i++){var el=document.getElementById('ir'+i);if(el)el.value=o.alpha[i]}}
if(o.phase===2&&irPoll){clearInterval(irPoll);irPoll=null}});}
document.getElementById('fConn').onsubmit=saveConn;document.getElementById('fMot').onsubmit=saveMot;document.getElementById('fIr').onsubmit=saveIr;document.getElementById('fPid').onsubmit=savePid;document.getElementById('bReset').onclick=resetE;tabs();
document.getElementById('bIrStart').onclick=function(){var d=document.getElementById('irDmm').value||100;ajax('/api/ir_autocalib','POST','start=1&d_mm='+encodeURIComponent(d),function(st,tx){if(st!==200){alert('Start failed');return}if(irPoll)clearInterval(irPoll);irPoll=setInterval(pollIrCalib,250)});};
document.getElementById('bIrCancel').onclick=function(){ajax('/api/ir_autocalib','POST','cancel=1',function(){if(irPoll){clearInterval(irPoll);irPoll=null}pollIrCalib()});};
function ledPost(r,g,b,a){ajax('/api/led','POST','r='+r+'&g='+g+'&b='+b+'&a='+(a!==undefined?a:255),function(){})}
document.querySelectorAll('[data-lr]').forEach(function(btn){btn.onclick=function(){ledPost(+btn.getAttribute('data-lr'),+btn.getAttribute('data-lg'),+btn.getAttribute('data-lb'),255)}});
document.getElementById('bLedOff').onclick=function(){ledPost(0,0,0,0)};
var sl=document.getElementById('sl'),sr=document.getElementById('sr');
sl.oninput=function(){document.getElementById('lv').textContent=sl.value};sr.oninput=function(){document.getElementById('rv').textContent=sr.value};
document.getElementById('bApply').onclick=function(){motorPost(sl.value,sr.value,0)};document.getElementById('bStop').onclick=function(){motorPost(0,0,1);sl.value=sr.value=1500;document.getElementById('lv').textContent=document.getElementById('rv').textContent='1500'};
ajax('/api/telemetry',0,0,function(st,tx){if(st!==200)return;var d;try{d=JSON.parse(tx)}catch(e){return}fillForm(d)});
setInterval(poll,200);
})();
</script></body></html>)HEROHTML";

void heroWebSendRootPage(ESP8266WebServer* server) {
  server->send_P(200, PSTR("text/html; charset=utf-8"), HTML_DOC);
}
