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

//Set TM1637 Pin
TM1637 display(sagment_clk, sagment_dio);

//Initial
String incomingByte;
long happyTime = 0;
int strength = 0;
long happyTime1;
long happyTime2;
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

  vibrate(0);

  Serial.begin(serial_rate);     // opens serial port, sets data rate to 9600 bps

  Serial.println("Welcome to X3 Plesure Service");
  Serial.println("Strength : 130 - 255");
  Serial.println("Time(ms)");
  Serial.println("Format for Input : #strength,time#");
  Serial.println("Example : #255,2000#");
  Serial.println("Waiting for Input . . . .");
  

  //Display Zone
  display.point(POINT_ON);

  display.display(0,0);
  display.display(1,0);
  display.display(2,15);
  display.display(3,0);

}

void(* reset) (void) = 0; //declare reset function @ address 0

void loop() {

      display.display(0,0);
      display.display(1,0);
      display.display(2,15);
      display.display(3,0);

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {

    // read the incoming byte:
    Serial.readStringUntil('#');

    //Read Strength
    incomingByte = Serial.readStringUntil(',');
    strength = incomingByte.toInt();

    //Read happyTime
    incomingByte = Serial.readStringUntil('#');
    happyTime = atol(incomingByte.c_str());

    Serial.print("Strength = ");
    Serial.println(strength);
    Serial.print("happyTime = ");
    Serial.println(happyTime);

    happyTime = getSecond(happyTime);

    heavenFloor = getHeavenFloor(strength);

    if (strength < 1 || strength > 255){
      throwError();
      reset();
    }

    if (happyTime < 1 || happyTime > 99000) {
      throwError();
      reset();
    }

    vibrate(strength);

    display.display(2,15);
    display.display(3,heavenFloor);

    for (happyTime ; happyTime > long(0) ; happyTime -= long(1000)){


      int x = getFirstPosition(happyTime);
      int y = getSecondPosition(happyTime);

      display.display(0,x);
      display.display(1,y);


      Serial.print("Time Left = ");
      Serial.print(happyTime / 1000);
      Serial.println(" seconds");
      Serial.print("happyTime = ");
      Serial.print(x);
      Serial.println(y);
      Serial.print("heavenFloor = ");
      Serial.println(heavenFloor);

      delay(1000);

    }

    vibrate(0);
    Serial.println("DONE");
    Serial.println("Waiting for Input . . . .");
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

long getSecond(long time) {

       time /=1000;
       return floor(time + 0.5) * 1000;  

}

void vibrate(int strength) {
  analogWrite(vibrator_pin, strength);
}

int getFirstPosition(long number) {
  return int((number / 10000) % 10);
}

int getSecondPosition(long number) {
  return int((number / 1000) % 10);
}

void throwError() {
  display.display(0,14);
  display.display(1,14);
  display.display(2,14);
  display.display(3,14);
  Serial.println("ERROR ! ! !");
  delay(3000);
  vibrate(255);
  delay(500);
}