#include <IRremote.h>

const byte ir=A0, l1=8, l2=9, l3=10 ;
unsigned long data;
IRrecv irrecv(ir);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(A0, INPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
}

void loop() {
  if(irrecv.decode(&results)){
    Serial.println(results.value);
    data = results.value;
    irrecv.resume();
    
    switch (data){
      case 1286666973:
      digitalWrite(l1, HIGH);
      delay(1000);
      digitalWrite(l1, LOW);
      break;
      
      case 1033561079:
      digitalWrite(l2, HIGH);
      delay(1000);
      digitalWrite(l2, LOW);
      break;
      
      case 1635910171:
      digitalWrite(l3, HIGH);
      delay(1000);
      digitalWrite(l3, LOW);
      break;
      }
    }
}

//1 16724175
//2 1033561079
//3 1635910171
