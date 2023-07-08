// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid = "Warnet Putri";
const char* password = "poiuytrewq";
char* host = "petanidigital.epizy.com";
const uint16_t port = 80;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setting WiFi
  WiFi.hostname("Petani Digital");
  WiFi.begin(ssid, password);
}

void loop() {
  // Baca nilai sensor
  int gas = analogRead(A0);

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
    // Pengiriman data ke server
    String Link;
    HTTPClient http;
    Link = "http://"+String(host)+"/terima_data.php?Ketinggian_Air="+String(gas);

    // Eksekusi link
    http.begin(client,Link);
    
    // Mode
    http.GET();

    // Akhiri HTTP
    http.end();

    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke ");
    Serial.println(ssid);
    Serial.print("Tersambung ke ");
    Serial.println(host);
    Serial.print("Kirim URL ");
    Serial.println(Link);

    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  delay(850);
}
