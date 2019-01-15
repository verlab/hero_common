#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ros.h>

#include <std_msgs/String.h>

// WiFi Definitions
const char WiFiAPPSK[] = "verlab1234";

// between 4 and 4096bytes
#define MEM_ALOC_SIZE 512
#define MEM_INIT_POS 0

#define CONFIG_VERSION "v10"

struct DATA {
    uint robot_id;
    char robot_desc[20];
    char ros_master_address[20];
    char wifi_ssid[20];
    char wifi_pass[20];
    char version_of_program[4];
} configurationData = {
  // The default values
  -1,
  "",
  "",
  "",
  "",
  CONFIG_VERSION
};

ESP8266WebServer server(80);

/* Wifi setup */
IPAddress ROS_MASTER_ADDRESS(10, 42, 0, 1); // ros master ip
boolean ROS_CONNECTED = false;

char* WIFI_SSID = "epuck_net"; // network name
char* WIFI_PASSWD = "epuck_9895"; // network password

/* ROS Node Instaciatation */
ros::NodeHandle nh;
// Make a chatter publisher
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

// Be polite and say hello
char hello[13] = "hello world!";
uint16_t period = 1000;
uint32_t last_time = 0;

//root page can be accessed only if authentification is ok
void handleRoot(){
  Serial.println("Enter handleRoot");

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS, configurationData);
  EEPROM.end();
  
  String content = "<!doctype html><html><head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <title>HERO - configuration panel</title> <link rel=\"stylesheet\" href=\"/css\"> </head><body class=\"bg-light\"> <div class=\"container\"> <div class=\"py-5 text-center\"> <img class=\"d-block mx-auto mb-4\" alt=\"\" width=\"72\" height=\"72\" src=\"data:image/svg+xml;utf8;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iaXNvLTg4NTktMSI/Pgo8IS0tIEdlbmVyYXRvcjogQWRvYmUgSWxsdXN0cmF0b3IgMTkuMC4wLCBTVkcgRXhwb3J0IFBsdWctSW4gLiBTVkcgVmVyc2lvbjogNi4wMCBCdWlsZCAwKSAgLS0+CjxzdmcgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgdmVyc2lvbj0iMS4xIiBpZD0iQ2FwYV8xIiB4PSIwcHgiIHk9IjBweCIgdmlld0JveD0iMCAwIDUxMiA1MTIiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUxMiA1MTI7IiB4bWw6c3BhY2U9InByZXNlcnZlIiB3aWR0aD0iNTEycHgiIGhlaWdodD0iNTEycHgiPgo8cmVjdCB4PSIyNDEiIHk9IjgxLjY3IiBzdHlsZT0iZmlsbDojOEY4RjhGOyIgd2lkdGg9IjMwIiBoZWlnaHQ9Ijc0LjY3Ii8+CjxyZWN0IHg9IjI1NiIgeT0iODEuNjciIHN0eWxlPSJmaWxsOiM2MDYwNjA7IiB3aWR0aD0iMTUiIGhlaWdodD0iNzQuNjciLz4KPHBvbHlnb24gc3R5bGU9ImZpbGw6IzAwODdGRjsiIHBvaW50cz0iNDM3LjQyMywyMTAuMDAxIDQzNy40MjMsMjQwLjAwMSA0MzcuNDIzLDI0MC4wMDEgNDM3LjQyMywzMjEuNjk4IDQzNy40MjMsMzIxLjY5OCAgIDQzNy40MjMsMzUxLjY5OCA1MTIsMzUxLjY5OCA1MTIsMjEwLjAwMSAiLz4KPHBvbHlnb24gc3R5bGU9ImZpbGw6IzAwQTVGRjsiIHBvaW50cz0iMCwzNTEuNjk4IDc0LjU3NywzNTEuNjk4IDc0LjU3NywzMjEuNjk4IDc0LjU3NywzMjEuNjk4IDc0LjU3NywyNDAuMDAxIDc0LjU3NywyNDAuMDAxICAgNzQuNTc3LDIxMC4wMDEgMCwyMTAuMDAxICIvPgo8cmVjdCB4PSI2Ny4yIiB5PSIxNDEuMzQiIHN0eWxlPSJmaWxsOiNEMEZERkE7IiB3aWR0aD0iMzc3LjYiIGhlaWdodD0iMzcwLjY2Ii8+CjxyZWN0IHg9IjI1NiIgeT0iMTQxLjM0IiBzdHlsZT0iZmlsbDojNzdGREY1OyIgd2lkdGg9IjE4OC44IiBoZWlnaHQ9IjM3MC42NiIvPgo8cmVjdCB4PSIxNTUuMTkiIHk9IjM2Mi4xOSIgc3R5bGU9ImZpbGw6IzYwNjA2MDsiIHdpZHRoPSIyMDEuNjIiIGhlaWdodD0iNjkuMDIiLz4KPHBhdGggc3R5bGU9ImZpbGw6I0ZGQTAxQTsiIGQ9Ik0yNDMuNDgsMjU1LjQxYzAsMjkuMDQtMjMuNjIsNTIuNjYtNTIuNjYsNTIuNjZjLTI5LjAzLDAtNTIuNjUtMjMuNjItNTIuNjUtNTIuNjYgIGMwLTI5LjAzLDIzLjYyLTUyLjY2LDUyLjY1LTUyLjY2QzIxOS44NiwyMDIuNzUsMjQzLjQ4LDIyNi4zOCwyNDMuNDgsMjU1LjQxeiIvPgo8cGF0aCBzdHlsZT0iZmlsbDojRkY2MzAwOyIgZD0iTTM3My44MywyNTUuNDFjMCwyOS4wNC0yMy42Miw1Mi42Ni01Mi42NSw1Mi42NmMtMjkuMDQsMC01Mi42Ni0yMy42Mi01Mi42Ni01Mi42NiAgYzAtMjkuMDMsMjMuNjItNTIuNjYsNTIuNjYtNTIuNjZDMzUwLjIxLDIwMi43NSwzNzMuODMsMjI2LjM4LDM3My44MywyNTUuNDF6Ii8+CjxwYXRoIHN0eWxlPSJmaWxsOiNGRTNGNEU7IiBkPSJNMzA0LjMzLDQ4LjMzYzAsMjYuNjUtMjEuNjgsNDguMzQtNDguMzMsNDguMzRzLTQ4LjMzLTIxLjY5LTQ4LjMzLTQ4LjM0UzIyOS4zNSwwLDI1NiwwICBTMzA0LjMzLDIxLjY4LDMwNC4zMyw0OC4zM3oiLz4KPHJlY3QgeD0iMjU2IiB5PSIzNjIuMTkiIHN0eWxlPSJmaWxsOiM0MDQwNDA7IiB3aWR0aD0iMTAwLjgxIiBoZWlnaHQ9IjY5LjAyIi8+CjxwYXRoIHN0eWxlPSJmaWxsOiNFMzAwMzA7IiBkPSJNMjU2LDk2LjY3VjBjMjYuNjUsMCw0OC4zMywyMS42OCw0OC4zMyw0OC4zM1MyODIuNjUsOTYuNjcsMjU2LDk2LjY3eiIvPgo8cGF0aCBzdHlsZT0iZmlsbDojQkZCRkJGOyIgZD0iTTE0MC4xOSwzNDcuMTl2OTkuMDJoMjMxLjYydi05OS4wMkgxNDAuMTl6IE0yMDYuODIsNDE2LjIxaC0zNi42M3YtMzkuMDJoMzYuNjNWNDE2LjIxeiAgIE0yNzUuMTgsNDE2LjIxaC0zOC4zNnYtMzkuMDJoMzguMzZWNDE2LjIxeiBNMzQxLjgxLDQxNi4yMWgtMzYuNjN2LTM5LjAyaDM2LjYzVjQxNi4yMXoiLz4KPHBhdGggc3R5bGU9ImZpbGw6IzhGOEY4RjsiIGQ9Ik0yNTYsMzQ3LjE5djMwaDE5LjE4djM5LjAySDI1NnYzMGgxMTUuODF2LTk5LjAySDI1NnogTTM0MS44MSw0MTYuMjFoLTM2LjYzdi0zOS4wMmgzNi42M1Y0MTYuMjF6Ii8+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+CjxnPgo8L2c+Cjwvc3ZnPgo=\"/> <h2>HERO configuration</h2> <p class=\"lead\">Edit basic robot configuration, Wifi credentials and calibration values.</p></div><div class=\"row\"> <div class=\"col-md-4 order-md-2 mb-4\"> <h4 class=\"d-flex justify-content-between align-items-center mb-3\"> <span class=\"text-muted\">Information</span> </h4> <ul class=\"list-group mb-3\"> <li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Robot ID</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$ROBOT_ID</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Flash chip ID</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$CHIP_ID</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Flash chip size</h6> <small class=\"text-muted\">(in bytes)</small> </div><span class=\"text-muted\">$FLASH_SIZE</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Flash chip speed</h6> <small class=\"text-muted\">(in Hz)</small> </div><span class=\"text-muted\">$FLASH_SPEED</span> </li></ul> <button class=\"btn btn-warning btn-lg btn-block\" type=\"submit\" id=\"btn-reset\">Reset memory</button> </div><div class=\"col-md-8 order-md-1\"> <h4 class=\"mb-3\">Configuration fields</h4> <form id=\"config-form\" class=\"needs-validation\" novalidate> <div class=\"mb-3\"> <label for=\"robotId\">Robot ID</label> <input type=\"number\" class=\"form-control\" name=\"robotId\" id=\"robotId\" placeholder=\"\" required value=\"$ROBOT_ID\" step=\"1\" max=\"999\"> <div class=\"invalid-feedback\"> Please a robot ID. </div></div><div class=\"mb-3\"> <label for=\"robotDescription\">Robot description (optional)</label> <input type=\"text\" class=\"form-control\" name=\"robotDescription\" id=\"robotDescription\" placeholder=\"Robot description...\" value=\"$ROBOT_DESC\" maxlength=\"19\"> </div><div class=\"row\"> <div class=\"col-md-6 mb-3\"> <label for=\"wificSSID\">Wifi client SSID</label> <input type=\"text\" class=\"form-control\" name=\"wificSSID\" id=\"wificSSID\" placeholder=\"Wifi SSID...\" required value=\"$WIFIC_SSID\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Valid Wifi SSID is required. </div></div><div class=\"col-md-6 mb-3\"> <label for=\"wificPassword\">Wifi client password</label> <input type=\"text\" class=\"form-control\" name=\"wificPassword\" id=\"wificPassword\" placeholder=\"Wifi password...\" required value=\"$WIFIC_PASSWD\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Valid Wifi client password is required. </div></div></div><div class=\"mb-3\"> <label for=\"rosMasterAddress\">ROS master address</label> <input type=\"text\" class=\"form-control\" name=\"rosMasterAddress\" id=\"rosMasterAddress\" placeholder=\"ROS Master hostname or IPv4 address...\" required value=\"$ROS_MASTER\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Please enter the ROS master address. </div></div><hr class=\"mb-4\"> <button class=\"btn btn-primary btn-lg btn-block\" type=\"submit\">Save parameters</button> </form> </div></div><footer class=\"my-5 pt-5 text-muted text-center text-small\"> <p class=\"mb-1\">&copy; 2018 HERO Robot \"The small and affordable swarm robot\" - VeRLab</p><ul class=\"list-inline\"> <li class=\"list-inline-item\"><a href=\"https://github.com/verlab/hero_driver/\">GitHub</a></li></ul> </footer> </div><script>function ajax_post(url, post_data, callback){var xmlhttp=new XMLHttpRequest(); xmlhttp.onreadystatechange=function(){if (xmlhttp.readyState==4 && xmlhttp.status==200){console.log('responseText:' + xmlhttp.responseText); try{var data=JSON.parse(xmlhttp.responseText);}catch (err){console.log(err.message + \" in \" + xmlhttp.responseText); return;}callback(data);}}; xmlhttp.open(\"POST\", url, true); xmlhttp.send(post_data);}document.getElementById(\"btn-reset\").addEventListener(\"click\", function(){ajax_post('/resetEEPROM', \"\", function(data){if (data.status==\"success\"){window.location.reload(true);}else{alert(\"An error happened, please check your internet connection, HERO source power and test again.\")}});}); document.getElementById(\"config-form\").addEventListener(\"submit\", function(e){e.preventDefault(); e.stopPropagation(); this.classList.add('was-validated'); if (this.checkValidity()===false){return false;}xhr=new XMLHttpRequest(); console.log(this.elements); var params=[].filter.call(this.elements, function(el){return true;}).filter(function(el){return !!el.name;}).filter(function(el){return !el.disabled;}).map(function(el){return encodeURIComponent(el.name) + '=' + encodeURIComponent(el.value);}).join('&'); ajax_post('/saveParams', params, function(data){if (data.status==\"success\"){window.location.reload(true);}else{alert(\"An error happened, please check your internet connection, HERO source power and test again.\")}}); return false;}); </script></body></html>";
  
  char tmp_str[20] = "";

  itoa(configurationData.robot_id, tmp_str, 10);
  content.replace("$ROBOT_ID", tmp_str);
  
  dtostrf(ESP.getFlashChipId(), 3, 1, tmp_str);
  content.replace("$CHIP_ID", tmp_str);

  dtostrf(ESP.getFlashChipSize(), 3, 1, tmp_str);
  content.replace("$FLASH_SIZE", tmp_str);

  dtostrf(ESP.getFlashChipSpeed(), 3, 1, tmp_str);
  content.replace("$FLASH_SPEED", tmp_str);

  content.replace("$ROBOT_DESC", configurationData.robot_desc);
  content.replace("$WIFIC_SSID", configurationData.wifi_ssid);
  content.replace("$WIFIC_PASSWD", configurationData.wifi_pass);
  content.replace("$ROS_MASTER", configurationData.ros_master_address);
  
  server.send(200, "text/html", content);
}

void handleSaveParams(){
  Serial.println("Enter handleSaveParams");
  
  String robot_id = server.arg("robotId");
  String robot_desc = server.arg("robotDescription");
  String wific_ssid = server.arg("wificSSID");
  String wific_pass = server.arg("wificPassword");
  String ros_master = server.arg("rosMasterAddress");

  char tmp_str[20] = "";

  configurationData.robot_id = robot_id.toInt();
  strcpy(configurationData.robot_desc, robot_desc.c_str());
  strcpy(configurationData.wifi_ssid, wific_ssid.c_str());
  strcpy(configurationData.wifi_pass, wific_pass.c_str());
  strcpy(configurationData.ros_master_address, ros_master.c_str());

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS, configurationData);
  EEPROM.end();

  String content = "{\"status\":\"success\"}";
  server.send(200, "application/json", content);
}

void handleCSS(){
  String css = "h2,h4,h6,p,ul{margin-top:0}h2,h4,h6,label{margin-bottom:.5rem}button,hr,input{overflow:visible}hr,p,ul{margin-bottom:1rem}.btn,img{vertical-align:middle}.btn-primary,.btn-warning{background-repeat:repeat-x}*,::after,::before{box-sizing:border-box}footer{display:block}.list-inline-item,label{display:inline-block}body{margin:0;font-family:-apple-system,BlinkMacSystemFont,\"Segoe UI\",Roboto,\"Helvetica Neue\",Arial,sans-serif,\"Apple Color Emoji\",\"Segoe UI Emoji\",\"Segoe UI Symbol\";font-size:1rem;font-weight:400;line-height:1.5;color:#212529;text-align:left;background-color:#fff}h2,h4,h6{font-family:inherit;font-weight:500;line-height:1.2;color:inherit}small{font-size:80%}a{color:#007bff;text-decoration:none;background-color:transparent;-webkit-text-decoration-skip:objects}a:hover{color:#0056b3;text-decoration:underline}img{border-style:none}button{border-radius:0;text-transform:none}button:focus{outline:dotted 1px;outline:-webkit-focus-ring-color auto 5px}.btn:focus,.form-control:focus{outline:0;box-shadow:0 0 0 .2rem rgba(0,123,255,.25)}button,input{margin:0;font-family:inherit;font-size:inherit;line-height:inherit}[type=submit],button{-webkit-appearance:button}[type=submit]::-moz-focus-inner,button::-moz-focus-inner{padding:0;border-style:none}h2{font-size:2rem}h4{font-size:1.5rem}h6{font-size:1rem}.lead{font-size:1.25rem;font-weight:300}.btn,small{font-weight:400}hr{box-sizing:content-box;height:0;margin-top:1rem;border:0;border-top:1px solid rgba(0,0,0,.1)}.list-inline{padding-left:0;list-style:none}.col-md-4,.col-md-6,.col-md-8,.container{padding-right:15px;padding-left:15px;width:100%}.container{margin-right:auto;margin-left:auto}@media (min-width:576px){.container{max-width:540px}}@media (min-width:768px){.container{max-width:720px}}@media (min-width:992px){.container{max-width:960px}}@media (min-width:1200px){.container{max-width:1140px}}.row{display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;margin-right:-15px;margin-left:-15px}.col-md-4,.col-md-6,.col-md-8{position:relative;min-height:1px}.btn,.form-control{padding:.375rem .75rem;line-height:1.5}@media (min-width:768px){.col-md-4{-ms-flex:0 0 33.333333%;flex:0 0 33.333333%;max-width:33.333333%}.col-md-6{-ms-flex:0 0 50%;flex:0 0 50%;max-width:50%}.col-md-8{-ms-flex:0 0 66.666667%;flex:0 0 66.666667%;max-width:66.666667%}.order-md-1{-ms-flex-order:1;order:1}.order-md-2{-ms-flex-order:2;order:2}}.form-control{display:block;width:100%;font-size:1rem;color:#495057;background-color:#fff;background-clip:padding-box;border:1px solid #ced4da;border-radius:.25rem;transition:border-color .15s ease-in-out,box-shadow .15s ease-in-out}@media screen and (prefers-reduced-motion:reduce){.form-control{transition:none}}.form-control::-ms-expand{background-color:transparent;border:0}.form-control:focus{color:#495057;background-color:#fff;border-color:#80bdff}.form-control::-webkit-input-placeholder{color:#6c757d;opacity:1}.form-control::-moz-placeholder{color:#6c757d;opacity:1}.form-control:-ms-input-placeholder{color:#6c757d;opacity:1}.form-control::-ms-input-placeholder{color:#6c757d;opacity:1}.form-control::placeholder{color:#6c757d;opacity:1}.form-control:disabled{background-color:#e9ecef;opacity:1}.btn-primary,.btn-primary:disabled{background-color:#007bff;color:#fff}.invalid-feedback{display:none;width:100%;margin-top:.25rem;font-size:80%;color:#dc3545}.btn{display:inline-block;text-align:center;white-space:nowrap;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;border:1px solid transparent;font-size:1rem;border-radius:.25rem;transition:color .15s ease-in-out,background-color .15s ease-in-out,border-color .15s ease-in-out,box-shadow .15s ease-in-out}@media screen and (prefers-reduced-motion:reduce){.btn{transition:none}}.btn:focus,.btn:hover{text-decoration:none}.btn:disabled{opacity:.65}.btn:not(:disabled):not(.disabled){cursor:pointer}.btn-primary:hover{color:#fff;border-color:#0062cc}.btn-primary:focus{box-shadow:0 0 0 .2rem rgba(0,123,255,.5)}.btn-primary:disabled{border-color:#007bff}.btn-warning,.btn-warning:disabled{color:#212529;background-color:#ffc107}.btn-warning:hover{color:#212529;border-color:#d39e00}.btn-warning:focus{box-shadow:0 0 0 .2rem rgba(255,193,7,.5)}.btn-warning:disabled{border-color:#ffc107}.btn-lg{padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem}.btn-block{display:block;width:100%}.bg-light{background-color:#f8f9fa!important}.d-block{display:block!important}.d-flex{display:-ms-flexbox!important;display:flex!important}.justify-content-between{-ms-flex-pack:justify!important;justify-content:space-between!important}.align-items-center{-ms-flex-align:center!important;align-items:center!important}.my-0{margin-top:0!important;margin-bottom:0!important}.mb-1{margin-bottom:.25rem!important}.mb-3{margin-bottom:1rem!important}.mb-4{margin-bottom:1.5rem!important}.my-5{margin-top:3rem!important;margin-bottom:3rem!important}.pt-5,.py-5{padding-top:3rem!important}.py-5{padding-bottom:3rem!important}.mx-auto{margin-right:auto!important;margin-left:auto!important}.text-center{text-align:center!important}.text-muted{color:#6c757d!important}@media print{*,::after,::before{text-shadow:none!important;box-shadow:none!important}a:not(.btn){text-decoration:underline}img{page-break-inside:avoid}h2,p{orphans:3;widows:3}h2{page-break-after:avoid}.container,body{min-width:992px!important}}.btn-primary,.btn-warning{text-shadow:0 -1px 0 rgba(0,0,0,.2);-webkit-box-shadow:inset 0 1px 0 rgba(255,255,255,.15),0 1px 1px rgba(0,0,0,.075);box-shadow:inset 0 1px 0 rgba(255,255,255,.15),0 1px 1px rgba(0,0,0,.075)}.btn-primary:active,.btn-warning:active{-webkit-box-shadow:inset 0 3px 5px rgba(0,0,0,.125);box-shadow:inset 0 3px 5px rgba(0,0,0,.125)}.btn:active{background-image:none}.btn-primary{background-image:-webkit-linear-gradient(top,#337ab7 0,#265a88 100%);background-image:-o-linear-gradient(top,#337ab7 0,#265a88 100%);background-image:-webkit-gradient(linear,left top,left bottom,from(#337ab7),to(#265a88));background-image:linear-gradient(to bottom,#337ab7 0,#265a88 100%);filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ff337ab7', endColorstr='#ff265a88', GradientType=0);filter:progid:DXImageTransform.Microsoft.gradient(enabled=false);border-color:#245580}.btn-primary:focus,.btn-primary:hover{background-color:#265a88;background-position:0 -15px}.btn-primary:active{background-color:#265a88;border-color:#245580}.btn-warning{background-image:-webkit-linear-gradient(top,#f0ad4e 0,#eb9316 100%);background-image:-o-linear-gradient(top,#f0ad4e 0,#eb9316 100%);background-image:-webkit-gradient(linear,left top,left bottom,from(#f0ad4e),to(#eb9316));background-image:linear-gradient(to bottom,#f0ad4e 0,#eb9316 100%);filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#fff0ad4e', endColorstr='#ffeb9316', GradientType=0);filter:progid:DXImageTransform.Microsoft.gradient(enabled=false);border-color:#e38d13}.btn-warning:focus,.btn-warning:hover{background-color:#eb9316;background-position:0 -15px}.btn-warning:active{background-color:#eb9316;border-color:#e38d13}.list-group{border-radius:4px;-webkit-box-shadow:0 1px 2px rgba(0,0,0,.075);box-shadow:0 1px 2px rgba(0,0,0,.075);display:-ms-flexbox;display:flex;-ms-flex-direction:column;flex-direction:column;padding-left:0;margin-bottom:0}/*! CSS Used from: Embedded */.container{max-width:960px}.lh-condensed{line-height:1.25}.list-group-item-action{width:100%;color:#495057;text-align:inherit}.list-group-item-action:focus,.list-group-item-action:hover{color:#495057;text-decoration:none;background-color:#f8f9fa}.list-group-item-action:active{color:#212529;background-color:#e9ecef}.list-group-item{position:relative;display:block;padding:.75rem 1.25rem;margin-bottom:-1px;background-color:#fff;border:1px solid rgba(0,0,0,.125)}.list-group-item:first-child{border-top-left-radius:.25rem;border-top-right-radius:.25rem}.list-group-item:last-child{margin-bottom:0;border-bottom-right-radius:.25rem;border-bottom-left-radius:.25rem}.list-group-item:focus,.list-group-item:hover{z-index:1;text-decoration:none}.list-group-item.disabled,.list-group-item:disabled{color:#6c757d;background-color:#fff}.list-group-item.active{z-index:2;color:#fff;background-color:#007bff;border-color:#007bff}.list-group-flush .list-group-item{border-right:0;border-left:0;border-radius:0}.list-group-flush:first-child .list-group-item:first-child{border-top:0}.list-group-flush:last-child .list-group-item:last-child{border-bottom:0}.list-group-item-primary{color:#004085;background-color:#b8daff}.list-group-item-primary.list-group-item-action:focus,.list-group-item-primary.list-group-item-action:hover{color:#004085;background-color:#9fcdff}.list-group-item-primary.list-group-item-action.active{color:#fff;background-color:#004085;border-color:#004085}.list-group-item-secondary{color:#383d41;background-color:#d6d8db}.list-group-item-secondary.list-group-item-action:focus,.list-group-item-secondary.list-group-item-action:hover{color:#383d41;background-color:#c8cbcf}.list-group-item-secondary.list-group-item-action.active{color:#fff;background-color:#383d41;border-color:#383d41}.list-group-item-success{color:#155724;background-color:#c3e6cb}.list-group-item-success.list-group-item-action:focus,.list-group-item-success.list-group-item-action:hover{color:#155724;background-color:#b1dfbb}.list-group-item-success.list-group-item-action.active{color:#fff;background-color:#155724;border-color:#155724}.list-group-item-info{color:#0c5460;background-color:#bee5eb}.list-group-item-info.list-group-item-action:focus,.list-group-item-info.list-group-item-action:hover{color:#0c5460;background-color:#abdde5}.list-group-item-info.list-group-item-action.active{color:#fff;background-color:#0c5460;border-color:#0c5460}.list-group-item-warning{color:#856404;background-color:#ffeeba}.list-group-item-warning.list-group-item-action:focus,.list-group-item-warning.list-group-item-action:hover{color:#856404;background-color:#ffe8a1}.list-group-item-warning.list-group-item-action.active{color:#fff;background-color:#856404;border-color:#856404}.list-group-item-danger{color:#721c24;background-color:#f5c6cb}.list-group-item-danger.list-group-item-action:focus,.list-group-item-danger.list-group-item-action:hover{color:#721c24;background-color:#f1b0b7}.list-group-item-danger.list-group-item-action.active{color:#fff;background-color:#721c24;border-color:#721c24}.list-group-item-light{color:#818182;background-color:#fdfdfe}.list-group-item-light.list-group-item-action:focus,.list-group-item-light.list-group-item-action:hover{color:#818182;background-color:#ececf6}.list-group-item-light.list-group-item-action.active{color:#fff;background-color:#818182;border-color:#818182}.list-group-item-dark{color:#1b1e21;background-color:#c6c8ca}.list-group-item-dark.list-group-item-action:focus,.list-group-item-dark.list-group-item-action:hover{color:#1b1e21;background-color:#b9bbbe}.list-group-item-dark.list-group-item-action.active{color:#fff;background-color:#1b1e21;border-color:#1b1e21}    .invalid-feedback{display:none;width:100%;margin-top:.25rem;font-size:80%;color:#dc3545;} .was-validated .form-control:invalid{border-color:#dc3545;}.was-validated .form-control:invalid:focus{border-color:#dc3545;box-shadow:0 0 0 .2rem rgba(220,53,69,.25);}";
  server.send(200, "text/css", css);
}

void handleResetEEPROM(){
    Serial.println("Enter handleResetEEPROM");

    char tmp_str[20] = "";

    configurationData.robot_id = -1;
    strcpy(configurationData.robot_desc,tmp_str);
    strcpy(configurationData.ros_master_address,tmp_str);
    strcpy(configurationData.wifi_ssid,tmp_str);
    strcpy(configurationData.wifi_pass,tmp_str);

    EEPROM.begin(MEM_ALOC_SIZE);
    EEPROM.put(MEM_INIT_POS, configurationData);
    EEPROM.end();
    
    String content = "{\"status\":\"success\"}";
    server.send(200, "application/json", content);
}

//no need authentification
void handleNotFound() {
  Serial.println("Enter handleNotFound");
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void initHardware() {
  Serial.begin(115200);
}

void setup() {
  initHardware();
  setupWiFi();
  server.on("/", handleRoot);
  server.on("/resetEEPROM", handleResetEEPROM);
  server.on("/saveParams", handleSaveParams);
  server.on("/css", handleCSS);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  /* Setup complete esp LED message */
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i <= 20; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(100);                   
  }
}

void setupWiFi() {
  // Do a little work to get a unique-ish name. 
  // Append the last two bytes of the MAC (HEX'd)
  WiFi.mode(WIFI_AP);
  
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "HERO_ROBOT_" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK, 8);
  
  //WiFi.mode(WIFI_AP_STA);
  
}

void loop() {
  server.handleClient();
  delay(1);
}


