#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  (50)
#define api A0    

short data;

const char* ssid = "Warnet Putri";
const char* password = "poiuytrewq";
const char* mqtt_server = "192.168.100.117";
int durasi,jarak;  

WiFiClient espClient;
PubSubClient client(espClient);

char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
  for (int i = 0; i < length; i++) {
  }
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
    } else {
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();
  Serial.begin(115200);
  
  pinMode(api,INPUT);
 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  
  data=analogRead(api);

  String keadaan;
  
  if(data<1024){
    snprintf (msg, MSG_BUFFER_SIZE, "Terdeteksi Api : Iya");
    }else{
    snprintf (msg, MSG_BUFFER_SIZE, "Terdeteksi Api : Tidak");
    }
  
  client.publish("sensor_api", msg);
  delay(1000);
}
