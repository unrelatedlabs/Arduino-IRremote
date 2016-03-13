
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <WiFiManager.h>

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>      //https://github.com/bblanchon/ArduinoJson
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <IRremote.h>


void server_loop(void);
void server_setup(void);

IRsend send;

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);           // set pin to input
  pinMode(D3, OUTPUT);           // set pin to input

  WiFiManager wifiManager;
  wifiManager.autoConnect("Pick ME ME ME");

  server_setup();

  send.sendLG(0xCCCCAA,24);

}

int t = 0;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D3, t++ & 1 ? HIGH : LOW);
  
  server_loop();
  
}



#include <WiFiClient.h>

 

MDNSResponder mdns;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
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
  digitalWrite(led, 0);
}
 
void server_setup(void){
   
  Serial.begin(115200);


  Serial.println("Hello");


  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
//  if (mdns.begin("esp8266", WiFi.localIP())) {
//    Serial.println("MDNS responder started");
//  }
  
  server.on("/", handleRoot);

  int t2 = 0;
  
  server.on("/on", [](){
    digitalWrite(D2,  HIGH );
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/off", [](){
    digitalWrite(D2,  LOW);
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/inline", [](){
    send.sendNEC(0x20df906f, 32);
    server.send(200, "text/plain", "this works as well mute");
  });

  server.on("/power", [](){
    send.sendNEC(0x0000000020DF10EF, 32);
    server.send(200, "text/plain", "this works as well power");
  });


  

  
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void server_loop(void){
  server.handleClient();
} 


