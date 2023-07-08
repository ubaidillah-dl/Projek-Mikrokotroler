// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid      = "Server";
const char* password  = "poiuytrewq";
const uint16_t port   = 80;
char* host            = "192.168.4.1";

const byte pot = A0;
long nilai, kecerahan;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(pot, INPUT);

  // Setting WiFi
  WiFi.hostname("Kamar Mandi");
  WiFi.begin(ssid, password);
}

void loop() {
  // Baca sensor
  nilai = analogRead(pot);  
    
  // Bila belum terhubung
  while(WiFi.status() !=WL_CONNECTED){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Menyambungkan ke ");
    Serial.println(ssid);
    delay(1000);
  }
  
  // Cek koneksi ke server
  WiFiClient client;
  if(!client.connect(host,port)){
    Serial.print("Menyambung ke ");
    Serial.println(host);
    return;
  }else{
    // Buat logikanya
    client.println("GET /kecerahan?value=" + String(nilai) + " HTTTP/1.1");
    client.println("Host: 192.168.4.1");
    client.println("Connection: close");
    client.println();

    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke Wifi    : ");
    Serial.println(ssid);
    Serial.print("Tersambung ke Server  : ");
    Serial.println(host);
    Serial.print("Nilai                 : ");
    Serial.println(nilai);
    
    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  delay(850);
}
