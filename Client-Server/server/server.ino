#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//=============================ESP_AP CREDENTIALS======================================
const char* ssid = "jio";
const char* password = "11223344";
int max_connection = 8;

//=====================================================================================

//===============================STATIC IP DECLARATION=================================
IPAddress staticIP(10,10,10,1); // IP address from Admin pannel 
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);
//=====================================================================================

int httpCode;

HTTPClient http;

ESP8266WebServer server(80); //Server on port 80


//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
void dro() {
  server.send(200, "text/plain", "Door Opened" );
  Serial.println("Door Opened");
  digitalWrite(5, HIGH);               
}
void drc() {
  server.send(200, "text/plain", "Door Closed" );
  Serial.println("Door Closed");
  digitalWrite(5, LOW);;               
}

//===============================================================
//                  SETUP
//===============================================================

void setup(void){
 
  Serial.begin(115200);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password, 1, false, max_connection); 
  WiFi.softAPConfig(staticIP, gateway, subnet);//Start HOTspot removing password will disable security
  Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());


  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
   pinMode(5, OUTPUT);
  
   delay(1000);
  
   server.on("/", handleRoot); //Which routine to handle at root location
   server.on("/dro", dro);
   server.on("/drc", drc);
   server.begin();                  //Start server
   Serial.println("HTTP server started");
}

//===============================================================
//                     LOOP
//===============================================================
void loop(void){

      server.handleClient();          //Handle client requests
} 
