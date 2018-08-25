//Import
#include "TM1637.h"

//Configuration
#define vibrator_pin 7
#define vibrator_high_pin 8
#define vibrator_low_pin 9
#define serial_rate 9600
#define sagment_low_pin 4
#define sagment_high_pin 5
#define sagment_clk 3
#define sagment_dio 2

//TM1637
TM1637 display(sagment_clk, sagment_dio);


String incomingByte;
int happyTime = 0;
int strength = 0;
int happyTime1;
int happyTime2;
int heavenFloor;

void setup() {
  //TM1637 Setup
  display.init();
  display.set(7);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  // put your setup code here, to run once:
  pinMode(vibrator_pin, OUTPUT);
  pinMode(vibrator_low_pin, OUTPUT);
  pinMode(vibrator_high_pin, OUTPUT);

  digitalWrite(vibrator_low_pin, LOW);
  digitalWrite(vibrator_high_pin, HIGH);

  digitalWrite(sagment_low_pin, LOW);
  digitalWrite(sagment_high_pin, HIGH);

  Serial.begin(serial_rate);     // opens serial port, sets data rate to 9600 bps
  Serial.println("Welcome to X3 Plesure Service");
  Serial.println("strength : 130 - 255");
  Serial.println("Time(ms)");
  Serial.println("Format for Input : #strength,time#");
  Serial.println("Waiting for input");
  analogWrite(vibrator_pin, 0);

  display.point(POINT_ON);

  display.display(0,0);
  display.display(1,1);
  display.display(2,2);
  display.display(3,3);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {

    // read the incoming byte:
    Serial.readStringUntil('#');
    incomingByte = Serial.readStringUntil(',');
    int strength = incomingByte.toInt();
    String incomingByte = Serial.readStringUntil('#');
    int happyTime = incomingByte.toInt();
    Serial.println(strength);
    Serial.println(happyTime);

    happyTime = getSecond(happyTime);

    analogWrite(vibrator_pin, strength);

    for (happyTime ; happyTime > 0 ; happyTime = happyTime - 1000){

      heavenFloor = getHeavenFloor(strength);

      happyTime1 = (happyTime / 10000) % 10;
      happyTime2 = (happyTime / 1000) % 10;

      Serial.println(happyTime);
      Serial.println(happyTime1);
      Serial.println(happyTime2);

      display.display(0,happyTime1);
      display.display(1,happyTime2);
      display.display(2,0);
      display.display(3,heavenFloor);

      delay(1000);
    }

      display.display(0,0);
      display.display(1,0);
      display.display(2,0);
      display.display(3,0);

    analogWrite(vibrator_pin, 0);
    Serial.println("DONE");
  }
}

int getHeavenFloor(int strength) {
    if (strength > 230) {return 7;}
    if (strength > 210) {return 6;}
    if (strength > 190) {return 5;}
    if (strength > 170) {return 4;}
    if (strength > 150) {return 3;}
    if (strength > 130) {return 2;}
    return 1;
  }

int getSecond(int time) {
       time /=1000;
       return floor(time + 0.5) * 1000;  
}