// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid = "Warnet Putri";
const char* password = "poiuytrewq";
char* host = "192.168.100.149";
const uint16_t port = 80;
const byte triger = 4, echo = 5;
long waktu, jarak;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  
  // Setting WiFi
  WiFi.hostname("Petani Digital");
  WiFi.begin(ssid, password);
}

void loop() {
  // Baca nilai sensor
  digitalWrite(triger, LOW);
  delayMicroseconds(2);
  digitalWrite(triger, HIGH);
  delayMicroseconds(2);
  digitalWrite(triger, LOW);

  waktu = pulseIn(echo,HIGH);
  jarak = (waktu/2)/28;
  
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
    String postData;
    HTTPClient http;
    postData = "Ketinggian_Air=" + String(jarak);

    // Eksekusi link
    http.begin(client,"http://" + String(host) + "/petanidigital/data/data_terima.php");
    http.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCode = http.POST(postData);
    String payload = http.getString();
    
    // Akhiri HTTP
    http.end();

    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke ");
    Serial.println(ssid);
    Serial.print("Tersambung ke ");
    Serial.println(host);
    Serial.print("Ketinggian ");
    Serial.println(jarak);

    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  delay(850);
}
