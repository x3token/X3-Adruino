String incomingByte;
int vibrator = 7;
int happyTime = 0;
int strength = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(vibrator, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial.println("Please Input 0 - 255");
  analogWrite(vibrator, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    Serial.readStringUntil('#');
    int strength = incomingByte.toInt();
    incomingByte = Serial.readStringUntil(',');
    int happyTime = incomingByte.toInt();
    String incomingByte = Serial.readStringUntil('#');
    Serial.println(strength);
    Serial.println(happyTime);
    analogWrite(vibrator, strength);
    delay(happyTime);
    Serial.println("DONE!!!");
  }

}
