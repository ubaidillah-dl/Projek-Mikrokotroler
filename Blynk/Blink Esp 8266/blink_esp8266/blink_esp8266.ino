unsigned int waktu_awal=0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  unsigned int waktu_sekarang = millis();
  
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  
  waktu_awal=waktu_sekarang;
}
