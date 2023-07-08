const byte senIR=4, led=5;

void setup() {
  Serial.begin(9600);
  pinMode(senIR, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  bool nilai = digitalRead(4);
  
  if(nilai == 0){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
