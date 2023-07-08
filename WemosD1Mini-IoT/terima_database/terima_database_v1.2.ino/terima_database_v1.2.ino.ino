// Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Identitas jaringan
const char* ssid = "Warnet Putri";
const char* password = "poiuytrewq";
char* host = "192.168.100.149";
const uint16_t port = 80;
const byte pompa = 5, irigasi = 4;

void setup() {
  // Inisialisasi dan komunikasi serial
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pompa, OUTPUT);
  pinMode(irigasi, OUTPUT);
  
  // Setting WiFi
  WiFi.hostname("Petani Digital");
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Pengiriman data ke server
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    // Tersambung ke ssid dan host
    Serial.println("");
    Serial.print("Tersambung ke ");
    Serial.println(ssid);
    Serial.print("Tersambung ke ");
    Serial.println(host);
    Serial.print("Status Pompa ");
    Serial.println(status_pompa);
    Serial.print("Status Irigasi ");
    Serial.println(status_irigasi);
    Serial.print("Status Ketinggian ");
    Serial.println(status_ketinggian);

    // Indikator Terhubung ke host
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);

    if(status_pompa == "Hidup"){
      Serial.println("Pompa Hidup");
      digitalWrite(pompa, HIGH);
    }else if(status_pompa == "Mati"){
      Serial.println("Pompa Mati");
      digitalWrite(pompa, LOW);
    }

     if(status_irigasi == "Terbuka"){
      Serial.println("Irigasi Dibuka");
      digitalWrite(irigasi, HIGH);
    }else if(status_irigasi == "Tertutup"){
      Serial.println("Irigasi Ditutup");
      digitalWrite(irigasi, LOW);
    }
    
  }
  delay(850);
}
