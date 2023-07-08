const byte hijau = 8, merah = 9, biru = 10;
char i;

void setup(){
  Serial.begin(9600);
  pinMode(hijau,OUTPUT);
  pinMode(merah,OUTPUT);
  pinMode(biru,OUTPUT);
}

void loop() {
 if(Serial.available()>0){
  i=Serial.read();
  Serial.println(i);
 }

 if(i == '1'){
  digitalWrite(hijau, HIGH);
  delay(1000);
  digitalWrite(hijau, LOW);
 }else if(i == '2'){
  digitalWrite(merah, HIGH);
  delay(1000);
  digitalWrite(merah, LOW);
 }else if(i == '3'){
  digitalWrite(biru, HIGH);
  delay(1000);
  digitalWrite(biru, LOW);
 }
 
}
