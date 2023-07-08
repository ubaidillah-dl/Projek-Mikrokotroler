const byte pinA = 13, pinB = 12, pinC = 11, pinD = 10, pinE = 9, pinF = 8, pinG = 7;
short t = 1000;

void setup() {
    pinMode (pinA,OUTPUT);
    pinMode (pinB,OUTPUT);
    pinMode (pinC,OUTPUT);
    pinMode (pinD,OUTPUT);
    pinMode (pinE,OUTPUT);
    pinMode (pinF,OUTPUT);
    pinMode (pinG,OUTPUT);
    
}

void loop() {
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 0);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 1);
    delay (t);

    //1
    digitalWrite (pinA, 1);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 1);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 1);
    digitalWrite (pinG, 1);
    delay (t);
    
    //2
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 1);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 0);
    digitalWrite (pinF, 1);
    digitalWrite (pinG, 0);
    delay (t);
     
     //3
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 1);
    digitalWrite (pinG, 0);
    delay (t);

     //4
    digitalWrite (pinA, 1);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 1);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 0);
    delay (t);

     //5
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 1);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 0);
    delay (t);

     //6
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 1);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 0);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 0);
    delay (t);

     //7
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 1);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 1);
    digitalWrite (pinG, 1);
    delay (t);

     //8
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 0);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 0);
    delay (t);

     //9
    digitalWrite (pinA, 0);
    digitalWrite (pinB, 0);
    digitalWrite (pinC, 0);
    digitalWrite (pinD, 0);
    digitalWrite (pinE, 1);
    digitalWrite (pinF, 0);
    digitalWrite (pinG, 0);
    delay (t);

    
}
