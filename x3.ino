String incomingByte;
int motor = 7;



void setup() {
  // put your setup code here, to run once:
  pinMode(motor, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial.println("Please Input 0 - 255");
  analogWrite(motor, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.readString();
    int power = incomingByte.toInt();
    Serial.println(incomingByte);
    analogWrite(motor, power);
    Serial.println("DONE!!!");
  }

}
