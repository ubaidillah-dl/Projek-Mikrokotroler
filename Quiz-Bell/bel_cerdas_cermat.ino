const byte tombolA = 2, tombolB = 3, tombolC = 4;
const byte lampuA = 8, lampuB = 9, lampuC = 10;
const int bel = 12, buzzer = 13;

void setup(){
  Serial.begin(9600);
    pinMode(tombolA, INPUT_PULLUP);
    pinMode(tombolB, INPUT_PULLUP);
    pinMode(tombolC, INPUT_PULLUP);
        
    pinMode(lampuA, OUTPUT); 
    
    pinMode(lampuB, OUTPUT);
    pinMode(lampuC, OUTPUT);

    
    pinMode(bel, OUTPUT);
    pinMode(buzzer, OUTPUT);
    
    digitalWrite(lampuA, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(lampuA, LOW);
    digitalWrite(buzzer, LOW);
    delay(600);

    digitalWrite(lampuB, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(lampuB, LOW);
    digitalWrite(buzzer, LOW);
    delay(600);

    digitalWrite(lampuC, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(lampuC, LOW);
    digitalWrite(buzzer, LOW);
    delay(600);   
}

void loop(){
    if ( digitalRead(tombolA)==LOW){
        digitalWrite(bel, HIGH);
        digitalWrite(lampuA, HIGH);
        digitalWrite(lampuA, HIGH);
        Serial.println("tombol 1 ditekan");
        
        while ( !digitalRead( tombolA) );
        digitalWrite(bel, LOW);
        digitalWrite(lampuA, LOW);
    } 
    
    else if ( digitalRead(tombolB)==LOW){
        digitalWrite(bel, HIGH);
        digitalWrite(lampuB, HIGH);
        Serial.println("tombol 2 ditekan");
      
        while (! digitalRead( tombolB) );
        digitalWrite(bel, LOW);
        digitalWrite(lampuB, LOW);
    } 
    
    else if ( digitalRead(tombolC)==LOW){
        digitalWrite(bel, HIGH);
        digitalWrite(lampuC, HIGH);      
        Serial.println("tombol 3 ditekan");
        
        while (! digitalRead( tombolC) );
        digitalWrite(bel, LOW);
        digitalWrite(lampuC, LOW);
    }
}
