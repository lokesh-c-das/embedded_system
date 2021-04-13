// Library initialization for servo motor
#include <Servo.h>
const int INPUT_PIN =10; // input pin number for push button
const int POT_PIN = A0; // Potentiometer input pin number
const int SERVO_PIN = 9; // Servo motor signal pin
static int movingAngle = 0;
int POT_VAL;
int  pushButtonState;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN,INPUT); // set input pin
  myServo.attach(SERVO_PIN); // attach servo motor pin
  Serial.begin(9600);
}
// This method for controlling servo motor: basically it rotates servo motor at specified angle
void controlServoMotor(int buttonState, int angle){
  myServo.write(angle);
  delay(10);
}
void loop() {
  // put your main code here, to run repeatedly:
  POT_VAL = analogRead(POT_PIN); //  Read potentiometer value
  pushButtonState = digitalRead(INPUT_PIN); // read push button value
  if(pushButtonState == LOW){
    // if button state is LOW which means button is active, we are moving our right: meaning I am increasing angle from current angle
    movingAngle += map(POT_VAL, 0,1023, 0,10); // moving servo motor 0-10 degree right based on potentiomenter values
    movingAngle = movingAngle < 180 ? movingAngle:180; // this is a simple echeck whether movingAngle is greater than 180 if it is then set to 180 otherwise set movingAngle itself
  }else{
    movingAngle -= map(POT_VAL, 0,1023, 0,10); // button is not active, rotate servo motor left: meaning that I am decreasing angle from current angle.
    movingAngle = movingAngle < 0 ? 0:movingAngle; // this is checking whether movingAngle is less than 0 if it is then set to 0 otherwise set to movingAngle itself.
  }
  Serial.print("Pot Angle :");
  Serial.println(movingAngle);
  controlServoMotor(pushButtonState, movingAngle); // this is the function where servo motor rotation has been implemented
  delay(500);
}
