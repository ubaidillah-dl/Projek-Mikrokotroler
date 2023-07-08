unsigned int waktu_awal=0;
const byte hijau=10, merah=9, biru=8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hijau,OUTPUT);
  pinMode(merah,OUTPUT);
  pinMode(biru,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int waktu_sekarang = millis();
  
  if(waktu_sekarang - waktu_awal == 500){
  digitalWrite(hijau,HIGH);
  }else if(waktu_sekarang - waktu_awal == 1000){
   digitalWrite(hijau,LOW);
  }else if(waktu_sekarang - waktu_awal == 1500){
   digitalWrite(merah,HIGH);
  }else if(waktu_sekarang - waktu_awal == 2000){
   digitalWrite(merah,LOW);}
   else if(waktu_sekarang - waktu_awal == 2500){
   digitalWrite(biru,HIGH);}
   else if(waktu_sekarang - waktu_awal == 3000){
   digitalWrite(biru,LOW);
waktu_awal=waktu_sekarang;}
}
