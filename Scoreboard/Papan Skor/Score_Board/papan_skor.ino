//memasukkan library-nya yang diperlukan
#include <SPI.h>
#include <EasyButton.h>
#include <DMD2.h>
#include <DMD.h>
#include <fonts/BigNumber.h>

//mengontrol seluruh tampilan DMD
SoftDMD dmd(1,1);  

//mendefinisikan pin sebagai tombol
#define btn1_pin A0
#define btn2_pin A1
#define btn3_pin A2
#define btn4_pin A3
#define btn5_pin A4

EasyButton btn1(btn1_pin);
EasyButton btn2(btn2_pin);
EasyButton btn3(btn3_pin);
EasyButton btn4(btn4_pin);
EasyButton btn5(btn5_pin);

byte score1 = 0;
byte score2 = 0;
byte scored_before = 0;

//fungsi tombol 1 untuk menambah score grub 1
void onBtn1Pressed(){
  score1++;
    if(score1 > 30 || score1 < 0){
      score1 = 0;
    }
    if (score1 < 10){
      dmd.drawString(19, -1, "0" + String(score1));
    }else{
      dmd.drawString(19, -1, String(score1));
    }
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15);
  dmd.drawBox(15, 5, 16, 7, scored_before == 1 ? GRAPHICS_ON : GRAPHICS_OFF);
  scored_before = 1;
}

//fungsi tombol 2 untuk mengurangi score grub 1
void onBtn2Pressed(){
 score1--;
  if(score1 > 30 || score1 < 0){
    score1 = 0;
  }
  if (score1 < 10){
   dmd.drawString(19, -1, "0" + String(score1));
  }else {
    dmd.drawString(19, -1, String(score1));
  }
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15);
  dmd.drawBox(15, 5, 16, 7, scored_before == 1 ? GRAPHICS_ON : GRAPHICS_OFF);
  scored_before = 1;
}

//fungsi tombol 3 untuk menambah score grub 2
void onBtn3Pressed(){
  score2++;
    if(score2 > 30 || score2 < 0){
      score2 = 0;
    }
    if (score2 < 10){
      dmd.drawString(0, -1, "0" + String(score2));
    }else {
      dmd.drawString(0, -1, String(score2));
    }
  dmd.drawBox(0, 14, 12, 15);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
  dmd.drawBox(15, 5, 16, 7, scored_before == 2 ? GRAPHICS_ON : GRAPHICS_OFF);
  scored_before = 2;
}

//fungsi tombol 4 untuk mengurangi score grub 2
void onBtn4Pressed(){
  score2--;
    if(score2 > 30 || score2 < 0){
      score2 = 0;
    }
    if (score2 < 10){
      dmd.drawString(0, -1, "0" + String(score2));
    }else{
      dmd.drawString(0, -1, String(score2));
    }
  dmd.drawBox(0, 14, 12, 15);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
  dmd.drawBox(15, 5, 16, 7, scored_before == 2 ? GRAPHICS_ON : GRAPHICS_OFF);
  scored_before = 2;
}

//fungsi tombol 5 untuk mereset score grub 1 dan grub 2
void onBtn5Pressed(){
  scored_before = 0;
  score1 = 0;
  score2 = 0;
  dmd.drawString(0,-1,F("00"));
  dmd.drawString(19, -1, F("00"));
  dmd.drawBox(14,4,17,8);
  dmd.drawBox(15, 5, 16, 7, GRAPHICS_OFF);
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
}

void setup() {
  dmd.setBrightness(60);
  dmd.selectFont(BigNumber);
  dmd.begin();
  dmd.drawString(0,-1,F("00"));
  dmd.drawString(19, -1, F("00"));
  dmd.drawBox(14,4,17,8);
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
  
  // inisiasi button
  btn1.begin();
  btn2.begin();
  btn3.begin();
  btn4.begin();
  btn5.begin();

  btn1.onPressedFor(100, onBtn1Pressed); //score akan bertambah setelah menekan selama 0,1 detik
  btn2.onPressedFor(1000, onBtn2Pressed); //score akan berkurang setelah menekan selama 1 detik
  btn3.onPressedFor(100, onBtn3Pressed); //score akan bertambah setelah menekan selama 0,1 detik
  btn4.onPressedFor(1000, onBtn4Pressed); //score akan berkurang setelah menekan selama 1 detik
  btn5.onPressedFor(2000, onBtn5Pressed); //semua score akan kembali setelah menekan selama 2 detik, untuk menghindari tertekan tanpa sengaja
}

void loop() {
  btn1.read();
  btn2.read();
  btn3.read();
  btn4.read();
  btn5.read();
}
