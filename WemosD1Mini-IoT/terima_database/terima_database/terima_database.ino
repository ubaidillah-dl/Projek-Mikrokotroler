// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid = "Warnet Putri";
const char* password = "poiuytrewq";
char* host = "192.168.100.149";
const uint16_t port = 80;
const byte led = 5;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT);

  // Setting WiFi
  WiFi.hostname("Sensor Gas");
  WiFi.begin(ssid, password);
}

void loop() {
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
    Link = "http://" + String(host) + "/sensor/ambil_data.php";

    // Eksekusi link
    http.begin(client,Link);
    
    // Mode
    http.GET();

    // Ambil nilai dari database
    String nilai_database = client.readStringUntil('\r');

    // Ubah jadi integer
    short intensitas = nilai_database.toInt();

    // Mengakhiri HTTP
    http.end();

    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke ");
    Serial.println(ssid);
    Serial.print("Tersambung ke ");
    Serial.println(host);
    Serial.print("Intensitas gas ");
    Serial.println(intensitas);

    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);

    if(intensitas>=250){
      Serial.println("Lampu hidup");
      digitalWrite(led, HIGH);
    }else{
      Serial.println("Lampu mati");
      digitalWrite(led, LOW);
    }
  }
  delay(850);
}
