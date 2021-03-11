#include <avr/io.h>
#include <avr/interrupt.h>

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
int extraTime = 0;
void setup() {
  cli(); // clear interrupt
  Serial.begin(9600);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 34286;
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<TOIE1);
  DDRB = 0b00100000;
  sei();
}
ISR(TIMER1_OVF_vect){
  if(TCNT1 <= 34286){
    Serial.println(TCNT1);
    PORTB ^= (1<<PORTB5);
    TCNT1 = 34286;
  }
  
}
// the loop function runs over and over again forever
void loop() {
  // wait for a second
}
