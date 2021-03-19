#include <Servo.h>
const int INPUT_PIN =10;
const int POT_PIN = A0;
const int SERVO_PIN = 9;
static int movingAngle = 0;
int POT_VAL;
int  pushButtonState;
int angle;
int pos;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN,INPUT);
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
}
void controlServo(int buttonState, int angle){
  myServo.write(angle);
  delay(10);
}
void loop() {
  // put your main code here, to run repeatedly:
  POT_VAL = analogRead(POT_PIN);
  pushButtonState = digitalRead(INPUT_PIN);
  if(pushButtonState == LOW){
    movingAngle += map(POT_VAL, 0,1023, 0,10);
    movingAngle = movingAngle < 180 ? movingAngle:0;
  }else{
    movingAngle -= map(POT_VAL, 0,1023, 0,10);
    movingAngle = movingAngle < 0 ? 0:movingAngle;
  }
  Serial.print("Pot Angle :");
  Serial.println(movingAngle);
  controlServo(pushButtonState, movingAngle);
  delay(500);
}
