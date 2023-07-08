const byte senSound=16, rly=5;

void setup() {
  Serial.begin(9600);
  pinMode(senSound, INPUT);
  pinMode(rly, OUTPUT);
}

void loop() {
  bool nilai = digitalRead(senSound);
  
  if(nilai == 0){
    digitalWrite(rly, HIGH);
    delay(3000);
    digitalWrite(rly, LOW);
  }else{
    digitalWrite(rly, LOW);
  }
}
