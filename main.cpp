#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<ESPAsyncTCP.h>
#include<ESPAsyncWebServer.h>

const char* ssid = "put SSID here";
const char* password = "put Password here";

// Assign output variables to GPIO pins
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

const uint8_t Relay1 = 2;
const uint8_t Relay2 = 0;

void connectify(const char* network,const char* pass){
  int times=0;
  Serial.println("connecting to ");
  Serial.print(network);
  Serial.println("----------------------------------------------------");
  WiFi.begin(network,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    times+=1;
  }
  Serial.println("----------------------------------------------------");
  Serial.println("Connecting tries = ");
  Serial.println(times);
  Serial.println("----------------------------------------------------");
  Serial.println("IP address ----> ");
  Serial.print(WiFi.localIP());

}


AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP 01 S Relay Board</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #90EE90}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP 01 S Relay Board</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  xhr.send();
}
</script>
<p align="centre" style="color:grey;font-size:30px;">Made By Aman Shaikh</p>

</body>
</html>
)rawliteral";


String outputState(int output){
  if(digitalRead(output)==0){
    return "checked";
  }
  else {
    return "";
  }
}



String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Relay1 status</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(Relay1) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Relay2 status</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"0\" " + outputState(Relay2) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);

  
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  
  connectify(ssid,password);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200,"text/html",index_html, processor);
  });

  server.on("/update",HTTP_GET, [](AsyncWebServerRequest *request){
    String inputMessage1;
    String inputMessage2;

    if(request->hasParam(PARAM_INPUT_1)&& request->hasParam(PARAM_INPUT_2)){
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  server.begin();

}

void loop() {
 
}