#include <avr/interrupt.h>
#include <arv/sleep.h>
char tick = '0';


void setup() {
  cli();
  // put your setup code here, to run once:
  DDRB |= 13;
  DDRB &= 10;

  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  PCICR |= 0b00000001;
  PCMSK0 |= _BV(PCINT0);

  Serial.begin(9600);
  sei();

}
ISR(PCINT0_vect){
  PORTB &= OFF ;
  TCNT1 = 2;
  TCCR1B = ;
  PORTB  ;
}

ISR(TIMER1_OVF_vect){
  if () {
    PORTB = ;
    TCNT1 = ;
  }else{
    PORTB;
    TCCR1B = ;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(value);
}
