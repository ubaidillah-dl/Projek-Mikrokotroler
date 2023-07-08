#include "SevSeg.h"
SevSeg sevseg;

void setup() {
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {13, 12, 11, 10, 9, 8, 7};
  bool resistorsOnSegments = true;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  for(int i = 0; i < 10; i++){
     sevseg.setNumber(i);
     sevseg.refreshDisplay(); 
     delay(2000);
   }
}
