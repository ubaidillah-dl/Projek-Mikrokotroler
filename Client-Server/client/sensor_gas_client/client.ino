#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

const char* ssid ="jio";
const char* password ="11223344";
IPAddress ip(10,10,10,55); 
IPAddress gateway(10,10,10,1); 
IPAddress subnet(255,255,255,0);


String message = "10101010";

ESP8266WebServer server(80);
void handleRoot() {
   server.send(200, "text/html", message);
   
}

//=========================================================================================
//                       SETUP 
//=========================================================================================
void setup() {
   server.on("/", handleRoot);

  server.begin();
    Serial.begin(115200);
    delay(500);
    WiFi.config(ip,gateway,subnet);
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT ...\n", t);
        Serial.flush();
        delay(1000);
    }
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);
    WiFi.begin(ssid,password);
    if(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    Serial.println("Connected");
  }
 pinMode(5,INPUT);
   
}
//========================================================================================
//                 LOOP  
//=======================================================================================
void loop() {
    
  server.handleClient();

    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        if(digitalRead(5) == HIGH)
        {  
        
          // http.begin("http://10.10.10.1/dro");//HTTP
          Serial.print("10.10.10.1/dro");
          int httpCode = http.GET();
           http.end();
        } 

        else if(digitalRead(5) == LOW)
        {
          //http.begin("http://10.10.10.1/drc");
          Serial.println("10.10.10.1/drc");
          int httpCode= http.GET();
          http.end();
        }


        
    }
}
