#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiServer server(80);

const char* ssid = "Server";
const char* password = "poiuytrewq";
const byte ledPin = D4;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    int kecerahan = request.substring(request.indexOf("value=") + 6).toInt();
    analogWrite(ledPin, kecerahan);

    Serial.print("Nilai sensor    : ");
    Serial.println(kecerahan);
    client.stop();
  } else {
    Serial.println("Menunggu client !");
  }
   delay(1000);
}
