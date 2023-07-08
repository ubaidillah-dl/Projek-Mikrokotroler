// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid      = "ssid";
const char* password  = "password";
char* host            = "192.168.115.250";
const uint16_t port   = 80;
const byte triger     = 12, echo = 13, pompa = 14, irigasi = 16;
long waktu, jarak, ketinggian;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(triger,       OUTPUT);
  pinMode(echo,         INPUT);
  pinMode(pompa,        OUTPUT);
  pinMode(irigasi,      OUTPUT);

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
  jarak = (waktu / 2) / 29.1;
  ketinggian = 3 - jarak;
  
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

    ////////////////////////////////////////// Kirim data ke server
    
    // Pengiriman data ke server
    String postData;
    HTTPClient http;
    postData = "Ketinggian_Air=" + String(ketinggian);

    // Eksekusi link
    http.begin(client,"http://" + String(host) + "/petanidigital/data/data_terima.php");
    http.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCode = http.POST(postData);
    String payload = http.getString();
    
    // Akhiri HTTP
    http.end();


    ////////////////////////////////////////// Ambil data pompa
    String Pompa;
    HTTPClient httpPompa;
    Pompa = "http://" + String(host) + "/petanidigital/data/data_pompa.php"; 
    
    // Eksekusi link
    httpPompa.begin(client,Pompa);
    httpPompa.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCodePompa = httpPompa.POST(Pompa);
    String status_pompa = httpPompa.getString();

    // Akhiri HTTP
    httpPompa.end();

    ////////////////////////////////////////// Ambil data irigasi
    
    // Pengiriman data ke server
    String Irigasi;
    HTTPClient httpIrigasi;
    Irigasi = "http://" + String(host) + "/petanidigital/data/data_irigasi.php"; 
    
    // Eksekusi link
    httpIrigasi.begin(client,Irigasi);
    httpIrigasi.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCodeIrigasi = httpIrigasi.POST(Irigasi);
    String status_irigasi = httpIrigasi.getString();

    // Akhiri HTTP
    httpIrigasi.end();

    ////////////////////////////////////////// Ambil data Ketinggian

    // Pengiriman data ke server
    String Ketinggian;
    HTTPClient httpKetinggian;
    Ketinggian = "http://" + String(host) + "/petanidigital/data/data_nilai.php"; 
    
    // Eksekusi link
    httpKetinggian.begin(client,Ketinggian);
    httpKetinggian.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCodeKetinggian = httpKetinggian.POST(Ketinggian);
    String status_ketinggian = httpKetinggian.getString();

    // Akhiri HTTP
    httpIrigasi.end();

    ////////////////////////////////////////// Ambil data usia

    // Pengiriman data ke server
    String Usia;
    HTTPClient httpUsia;
    Usia = "http://" + String(host) + "/petanidigital/data/data_usia.php"; 
    
    // Eksekusi link
    httpUsia.begin(client,Usia);
    httpUsia.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCodeUsia = httpUsia.POST(Usia);
    String status_usia = httpUsia.getString();

    // Akhiri HTTP
    httpIrigasi.end();

    ////////////////////////////////////////// Ambil data otomatis

    // Pengiriman data ke server
    String Otomatis;
    HTTPClient httpOtomatis;
    Otomatis = "http://" + String(host) + "/petanidigital/data/data_logika.php"; 
    
    // Eksekusi link
    httpOtomatis.begin(client,Otomatis);
    httpOtomatis.addHeader("Content-Type","application/x-www-form-urlencoded");
    
    // Mode
    auto httpCodeOtomatis = httpOtomatis.POST(Otomatis);
    String status_otomatis = httpOtomatis.getString();

    // Akhiri HTTP
    httpOtomatis.end();
    
    ////////////////////////////////////////// Logika data mode manual

    if(status_pompa == "Hidup"){
      digitalWrite(pompa, HIGH);
    }else if(status_pompa == "Mati"){
      digitalWrite(pompa, LOW);
    }

     if(status_irigasi == "Terbuka"){
      digitalWrite(irigasi, HIGH);
    }else if(status_irigasi == "Tertutup"){
      digitalWrite(irigasi, LOW);
    }    
    
    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke : ");
    Serial.println(ssid);
    Serial.print("Tersambung ke : ");
    Serial.println(host);
    Serial.print("Data sensor   : ");
    Serial.println(jarak);
    Serial.print("Pompa         : ");
    Serial.println(status_pompa);
    Serial.print("Irigasi       : ");
    Serial.println(status_irigasi);
    Serial.print("Ketinggian    : ");
    Serial.println(status_ketinggian);
    Serial.print("Usia          : ");
    Serial.println(status_usia);
    Serial.print("Otomatis      : ");
    Serial.println(status_otomatis);
    
    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  delay(850);
}
