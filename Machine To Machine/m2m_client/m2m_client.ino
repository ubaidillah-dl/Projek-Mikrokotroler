// Library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid ="Access Point";
const char* password ="accesspoint";

const byte pir = 5;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(pir,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setting WiFi
  WiFi.begin(ssid,password);

  // Bila belum tersambung
  while (WiFi.status() != WL_CONNECTED){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Menyambungkan ke ");
    Serial.println(ssid);
    delay(1000);
  }
}

void loop() {
  // Bila sudah terhubung
  if((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    WiFiClient client;
      
    // Cek input pin
    if(digitalRead(pir) == HIGH){ 
      http.begin(client, "http://192.168.4.1/pir");
        
      http.GET();

      http.end();
    }    
  }
}

   
