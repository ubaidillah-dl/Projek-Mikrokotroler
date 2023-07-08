#include <NewPing.h>
#define TRIGGER_PIN  16  
#define ECHO_PIN     14  
#define MAX_DISTANCE 100 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

int dinamoKanan=5;
int dinamoKiri=4;
int jarak=0;

void setup() {
  Serial.begin(115200);
  pinMode(dinamoKiri,OUTPUT);
  pinMode(dinamoKanan,OUTPUT);
  delay(10000);
}

void loop() {
  delay(50);         
  jarak=sonar.ping_cm();           
  Serial.print("Ping: ");
  Serial.print(jarak); 
  Serial.println("cm");
  if(jarak==0){
    digitalWrite(dinamoKiri,HIGH);
    digitalWrite(dinamoKanan,HIGH);
  }
  else{
    digitalWrite(dinamoKiri,HIGH);
    digitalWrite(dinamoKanan,HIGH);
    jarak=sonar.ping_cm();
    if(jarak<10){
      digitalWrite(dinamoKiri,LOW);
      digitalWrite(dinamoKanan,LOW);
      delay(2000);
      
      digitalWrite(dinamoKiri,HIGH);
      digitalWrite(dinamoKanan,LOW);
      delay(1000);
      
      digitalWrite(dinamoKiri,LOW);
      digitalWrite(dinamoKanan,LOW);
      delay(2000);
    }
  }
}
