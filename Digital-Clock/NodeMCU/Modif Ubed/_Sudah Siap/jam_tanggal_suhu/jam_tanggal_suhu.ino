

#include <FS.h>
#include <SPI.h>
#include <Wire.h>
#include <HJS589.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include <fonts/ElektronMart5x6.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/ElektronMart6x16.h>

#include "PrayerTimes.h"
#include "WebPage.h"

RtcDS3231<TwoWire> Rtc(Wire);

struct ConfigWifi {
  char wifissid[64];
  char wifipassword[64];
};

struct ConfigDisp {
  byte cerah;
};

const byte buzzer = 3;

byte pin_led = 2;

RtcDateTime now;
char weekDay[][7] = {"AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUMAT", "SABTU", "AHAD"};
char monthYear[][10] = {"DESEMBER", "JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER"};

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
HJS589 Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

ESP8266WebServer server(80);

const char* password  = "10052002";
const char* mySsid    = "Jam Digital";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

const char *fileconfigdisp = "/configdisp.json";
ConfigDisp configdisp;

const char *fileconfigwifi = "/configwifi.json";
ConfigWifi configwifi;

void buildXML() {
  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  XML = "<?xml version='1.0'?>";
  XML += "<t>";
  XML += "<rWifissid>";
  XML += configwifi.wifissid;
  XML += "</rWifissid>";
  XML += "<rYear>";
  XML += now.Year();
  XML += "</rYear>";
  XML += "<rMonth>";
  XML += now.Month();
  XML += "</rMonth>";
  XML += "<rDay>";
  XML += now.Day();
  XML += "</rDay>";
  XML += "<rHour>";
  if (now.Hour() < 10) {
    XML += "0";
    XML += now.Hour();
  } else {
    XML += now.Hour();
  }
  XML += "</rHour>";
  XML += "<rMinute>";
  if (now.Minute() < 10) {
    XML += "0";
    XML += now.Minute();
  } else {
    XML += now.Minute();
  }
  XML += "</rMinute>";
  XML += "<rSecond>";
  if (now.Second() < 10) {
    XML += "0";
    XML += now.Second();
  } else {
    XML += now.Second();
  }
  XML += "</rSecond>";
  XML += "<rTemp>";
  XML += temp.AsFloatDegC();
  XML += "</rTemp>"; 
  XML += "<rCerah>";
  XML += configdisp.cerah;
  XML += "</rCerah>";
  XML += "</t>";
}

void handleXML() {
  buildXML();
  server.send(200, "text/xml", XML);
}

void wifiConnect() {
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(configwifi.wifissid, configwifi.wifipassword);
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(pin_led, !digitalRead(pin_led));
    if (millis() - startTime > 3000) break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(pin_led, HIGH);
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(mySsid, password);
    digitalWrite(pin_led, LOW);
  }
  WiFi.printDiag(Serial);
}

void ICACHE_RAM_ATTR refresh() {
  Disp.refresh();
  timer0_write(ESP.getCycleCount() + 40000);
}

void Disp_init() {
  Disp.start();
  timer0_attachInterrupt(refresh);
  timer0_write(ESP.getCycleCount() + 40000);
  Disp.clear();
}

void LoadDataAwal() {
  if (configdisp.cerah == 0) {
    configdisp.cerah = 100;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(50);

  byte rtn = I2C_ClearBus();
  if (rtn != 0) {
    if (rtn == 1) {
    } else if (rtn == 2) {
    } else if (rtn == 3) {
    }
  } else {
    Wire.begin();
  }

  Rtc.Begin();
  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true);
  }

  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

  pinMode(pin_led, OUTPUT);

  SPIFFS.begin();
  loadWifiConfig(fileconfigwifi, configwifi);
  loadDispConfig(fileconfigdisp, configdisp);

  LoadDataAwal();

  WiFi.hostname("elektronmart");
  WiFi.begin(configwifi.wifissid, configwifi.wifipassword);

  wifiConnect();

  server.on("/", []() {
    server.send_P(200, "text/html", setwaktu);

    if (server.hasArg("date")) {
      uint16_t jam;
      uint8_t menit, detik;
      String sd = server.arg("date"), lastSd;

      jam = ((sd[0] - '0') * 1000) + ((sd[1] - '0') * 100) + ((sd[2] - '0') * 10) + (sd[3] - '0');
      menit = ((sd[5] - '0') * 10) + (sd[6] - '0');
      detik = ((sd[8] - '0') * 10) + (sd[9] - '0');

      if (sd != lastSd) {
        RtcDateTime now = Rtc.GetDateTime();
        uint8_t hour = now.Hour();
        uint8_t minute = now.Minute();
        Rtc.SetDateTime(RtcDateTime(jam, menit, detik, hour, minute, 0));
        lastSd = sd;
      }
      server.send ( 404 , "text", message );
    }

    if (server.hasArg("time")) {
      String st = server.arg("time"), lastSt;
      uint8_t jam = ((st[0] - '0') * 10) + (st[1] - '0'), menit = ((st[3] - '0') * 10) + (st[4] - '0');

      if (st != lastSt) {
        RtcDateTime now = Rtc.GetDateTime();
        uint16_t year = now.Year();
        uint8_t month = now.Month();
        uint8_t day = now.Day();
        Rtc.SetDateTime(RtcDateTime(year, month, day, jam, menit, 0));
        lastSt = st;
      }
      server.send ( 404 , "text", message );
    }
  });

  server.on("/toggle", toggleLED);

  server.on("/settingdisp", HTTP_POST, handleSettingDispUpdate);
  server.on ( "/xml", handleXML) ;

  server.begin();
  Serial.println("HTTP server started");

  BuzzerPendek();

  Disp_init();

  Disp.setBrightness(configdisp.cerah);
}

void loadDispConfig(const char *fileconfigdisp, ConfigDisp &configdisp) {
  File configFileDisp = SPIFFS.open(fileconfigdisp, "r");

  if (!configFileDisp) {
    return;
  }

  size_t size = configFileDisp.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileDisp.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    return;
  }

  configdisp.cerah = doc["cerah"];
  configFileDisp.close();
}

void handleSettingDispUpdate() {
  timer0_detachInterrupt();
  String datadisp = server.arg("plain");

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, datadisp);

  File configFileDisp = SPIFFS.open(fileconfigdisp, "w");

  if (!configFileDisp) {
    return;
  }

  serializeJson(doc, configFileDisp);

  if (error) {
    return;
  } else {
    configFileDisp.close();

    server.send(200, "application/json", "{\"status\":\"ok\"}");

    loadDispConfig(fileconfigdisp, configdisp);

    delay(500);
    timer0_attachInterrupt(refresh);
    timer0_write(ESP.getCycleCount() + 40000);

    Disp.setBrightness(configdisp.cerah);
  }
}

void loadWifiConfig(const char *fileconfigwifi, ConfigWifi &configwifi) {
  File configFileWifi = SPIFFS.open(fileconfigwifi, "r");

  if (!configFileWifi) {
    return;
  }

  size_t size = configFileWifi.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileWifi.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    return;
  }

  strlcpy(configwifi.wifissid, doc["wifissid"] | "Jam Digital", sizeof(configwifi.wifissid));
  strlcpy(configwifi.wifipassword, doc["wifipassword"] | "10052002", sizeof(configwifi.wifipassword));
  configFileWifi.close();
}

void handleSettingWifiUpdate() {
  timer0_detachInterrupt();
  String data = server.arg("plain");

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, data);
  File configFile = SPIFFS.open("/configwifi.json", "w");
  
  if (!configFile) {
    return;

  }

  serializeJson(doc, configFile);

  if (error) {
    return;
  } else {

    configFile.close();
    server.send(200, "application/json", "{\"status\":\"ok\"}");
    loadWifiConfig(fileconfigwifi, configwifi);

    delay(500);
    timer0_attachInterrupt(refresh);
    timer0_write(ESP.getCycleCount() + 40000);
  }
}

uint8_t tampilanutama;

void loop() {
  server.handleClient();

  switch (tampilanutama) {
    case 0 :
      JamJatuhPulse();
      break;
    case 1 :
      JamDanTanggal();
      break;
  }
}

void JamJatuhPulse() {
  static uint8_t y, d, pulse;
  static uint32_t pM, pMPulse;
  uint32_t cM = millis();

  if (cM - pMPulse >= 100) {
    pMPulse = cM;
    pulse++;
  }

  if (pulse > 8) {
    pulse = 0;
  }

  if (cM - pM > 25) {
    if (d == 0 and y < 32) {
      pM = cM;
      y++;
    }
    if (d  == 1 and y > 0) {
      pM = cM;
      y--;
    }
  }

  if (cM - pM > 120000 and y == 32) {
    d = 1;
  }

  if (y == 32) {
    Disp.drawRect(15, 3 + pulse, 18, 11 - pulse, 0, 1);
  }

  if (y < 32) {
    Disp.drawRect(15, 3, 18, 11, 0, 0);
  }

  if (y == 0 and d == 1) {
    d = 0;
    Disp.clear();
    tampilanutama = 1;
  }
  TampilJamDinamis(y - 32);
}

void TampilJamDinamis(uint32_t y) {
  RtcDateTime now = Rtc.GetDateTime();
  char jam[3], menit[3], detik[3];
  
  sprintf(jam, "%02d", now.Hour());
  sprintf(menit, "%02d", now.Minute());
  sprintf(detik, "%02d", now.Second());

  Disp.setFont(ElektronMart6x16);
  Disp.drawText(1, y, jam);

  Disp.setFont(ElektronMart5x6);
  Disp.drawText(20, y, menit);

  Disp.setFont(ElektronMart5x6);
  Disp.drawText(20, y + 8, detik);
}

void TampilJamKecil() {
  static uint32_t pM, pMJam;
  uint32_t cM = millis();
  static boolean kedip;

  RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];

  if (cM - pMJam >= 1000) {
    pMJam = cM;

    sprintf(jam, "%02d:%02d", now.Hour(), now.Minute());
    Disp.setFont(ElektronMart5x6);
    textCenter(0, jam);
  }
}

void BuzzerPanjang() {
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(50);
}

void BuzzerPendek() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(50);
}

void JamDanTanggal() {
  TampilJamKecil();

  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();

  char suhu[2];
  static char tanggalan[22];
  static uint32_t pM, x, Speed = 90;
  int celsius = temp.AsFloatDegC(), width = Disp.width(), koreksisuhu = 2;

  Disp.setFont(ElektronMart6x8);
  sprintf(tanggalan, "%s %02d %s %02d SUHU %dC", weekDay[now.DayOfWeek()], now.Day(), monthYear[now.Month()], now.Year(), celsius - koreksisuhu);
  int fullScroll = Disp.textWidth(tanggalan) + width;
  if ((millis() - pM) > Speed) {
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      tampilanutama = 0;
    }
    Disp.drawText(width - x, 8, tanggalan);
  }
}

void textCenter(int y, String Msg) {
  byte center = byte ((Disp.width() - Disp.textWidth(Msg)) / 2);
  Disp.drawText(center, y, Msg);
}

void toggleLED() {
  digitalWrite(pin_led, !digitalRead(pin_led));
  server.send_P(200, "text/html", setwaktu);
}

int I2C_ClearBus() {
#if defined(TWCR) && defined(TWEN)
  TWCR &= ~(_BV(TWEN));
#endif

  pinMode(SDA, INPUT_PULLUP);
  pinMode(SCL, INPUT_PULLUP);
  delay(2500);  

  boolean SCL_LOW = (digitalRead(SCL) == LOW); 
  if (SCL_LOW) {
    return 1; 
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW); 
  int clockCount = 20; 

  while (SDA_LOW && (clockCount > 0)) { 
    clockCount--;
    pinMode(SCL, INPUT); 
    pinMode(SCL, OUTPUT); 
    delayMicroseconds(10); 
    pinMode(SCL, INPUT);
    pinMode(SCL, INPUT_PULLUP); 
    delayMicroseconds(10); 
    
    SCL_LOW = (digitalRead(SCL) == LOW);
    int counter = 20;
    while (SCL_LOW && (counter > 0)) { 
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { 
      return 2; 
    }
    SDA_LOW = (digitalRead(SDA) == LOW); 
  }
  if (SDA_LOW) { 
    return 3; 
  }

  pinMode(SDA, INPUT); 
  pinMode(SDA, OUTPUT);  
  delayMicroseconds(10); 
  pinMode(SDA, INPUT); 
  pinMode(SDA, INPUT_PULLUP);
  delayMicroseconds(10);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  return 0;
}

/*
Pin on  DMD P10     GPIO      NODEMCU               Pin on  DS3231      NODEMCU                   Pin on  Buzzer       NODEMCU
        2  A        GPIO16    D0                            SCL         D1 (GPIO 5)                       +            RX (GPIO 3)
        4  B        GPIO12    D6                            SDA         D2 (GPIO 4)                       -            GND
        8  CLK      GPIO14    D5                            VCC         3V
        10 SCK      GPIO0     D3                            GND         GND
        12 R        GPIO13    D7
        1  NOE      GPIO15    D8
        3  GND      GND       GND
*/      
