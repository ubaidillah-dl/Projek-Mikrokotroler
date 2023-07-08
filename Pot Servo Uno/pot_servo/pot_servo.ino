#include<Servo.h>
Servo servo;

const byte potensio = A0;
short sudut, nilai;

void setup() {
  Serial.begin(9600);
  pinMode(potensio, INPUT);
  servo.attach(5);
}

void loop() {
  nilai = analogRead(potensio);
  sudut = map(nilai, 0,1023,0,155);
  servo.write(sudut);
} 
