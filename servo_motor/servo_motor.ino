/**
* Code for controlling servo motor
**/

#include <Servo.h>

Servo myservo;
int const POT_PIN = A0;
int POT_VAL;
int angle;
int pos = 0;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  POT_VAL = analogRead(POT_PIN);
  Serial.print("Analog read value:");
  Serial.print(POT_VAL);
  angle = map(POT_VAL,0,1023,0,179);
  Serial.print(", Angle: ");
  Serial.println(angle);

  myservo.write(angle);
  delay(15);

}
