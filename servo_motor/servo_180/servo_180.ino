
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
  for(pos=0; pos<=180;pos +=1){
    myservo.write(pos);
    delay(10);
  }
  for(pos = 180; pos >= 0; pos -= 1)
  {                                
    myservo.write(pos);  // Move to next position
    delay(10);               // Short pause to allow it to move
  }

}
