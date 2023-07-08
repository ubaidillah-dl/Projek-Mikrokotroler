#include<Servo.h>
Servo servo;

short sudut;
const byte ain1 = D5, ain2 = D0; 

void setup() {
  Serial.begin(9600);
 
  pinMode(ain1,OUTPUT);
  pinMode(ain2,OUTPUT);
  servo.attach(D1);
}
 
void loop() {
  
  analogWrite(ain1,255); 
  analogWrite(ain2,0);
  servo.write(0);

  delay(4000);
  
  analogWrite(ain1,0); 
  analogWrite(ain2,0);
  servo.write(90);
  
  delay(1000);
  
  analogWrite(ain1,0); 
  analogWrite(ain2,255);
  servo.write(0);

  delay(4000);
 
  analogWrite(ain1,0); 
  analogWrite(ain2,0);
  servo.write(90);
  
  delay(1000);
   
}
