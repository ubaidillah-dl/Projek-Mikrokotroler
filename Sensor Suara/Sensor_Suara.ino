const byte sensor=A0, led=5, buzzer=4;
short data;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  data = analogRead(sensor);
  Serial.println(data);
  
  if(data > 99){
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(2000);
     digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }else{
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
}
