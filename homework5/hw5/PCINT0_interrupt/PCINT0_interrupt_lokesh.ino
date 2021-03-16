/**
** User: Lokesh
*  Develop By: Lokesh
***/

#include <avr/interrupt.h>
#include <avr/sleep.h>

int inPin = 10; // Pushbutton connected to pin 10
int val = 0; // variable to store the input value read;
int ovfCnt = 0; // Let's count the number of counter overflows
int state = 0; // To check whether LED is ON or Off

void setup() {
  cli();  // Disable/clear the interrupt
  
  // Set the Pin 13 as output and 10 as input :  Writing a 1 makes output...0 makes input
  DDRB |=(1<<PORTB5);
  DDRB &=~(1<<PORTB2);
  

  // Control regs for Timer 1, disable unless sw press
  TCCR1A =  0b000000;// Set Normal Mode
  TCCR1B = (1<<CS12)|(1<<CS10); // Set Prescal 1024
  TIMSK1 = (1<<TOIE1); // Enable TIME overflow

  // ENABLE THE INTERRUPT BUT DO NOT CONNECT TCNT1 TO A SOURCE

  // Control regs for PCI
  PCICR = (1<<PCIE0); // activate control register at PORT B
  PCMSK0 = (1<<PCINT2); // Register PIN change interrupt at pin 10
  
  // Set the LED to OFF
  PORTB &= ~(1<<PORTB5); 
  Serial.begin(9600); // Initialize serial monitor, only for debug

  // Turn off the global interrupts to test the port configuration.
  sei(); // Set global Interrupt
}

/* INTERRUPT SERVICE ROUTINE DEFINITIONS */

//******** Pin change ISR
// ISR for pin change interrupt capture, set Timer 1 for 2 sec count
ISR(PCINT0_vect) {

  // SET UP TIMER CONTROL REGISTERS FOR OVERFLOW OPERATION
  TCCR1A = 0b000000 ; // Set to Mode Normal
  TCCR1B = (1<<CS12)|(1<<CS10); // <-- no input capture, normal operation, prescale clock by 1/1024
  // NO NEED TO INIT TCCR1C --> INITIALIZED TO REQUIRED VARIABLE ON STARTUP.

  // Enable overflow interrupts
  TCNT1 = 0x85ED; // set value for 2 sec count
  Serial.println("Pressed");

}

ISR(TIMER1_OVF_vect) {
  
  if (state == 0) {
    // Cut the light on and set the count for 3 seconds.
    PORTB |= (1 << PORTB5); // Turn ON LED at digital pin 13
    TCNT1 = 0x48E4; // 3 second timer
  } else {
    // Cut the light off, disable the timer counter
    PORTB &= ~(1 << PORTB5); // 
    TCCR1B = 0x00;  // Disconnect the source for TCNT1
  }
  ovfCnt++; // Count how many times interrupt occured.
  Serial.print(ovfCnt);
  state = !state;

}
void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(inPin);
  Serial.print("The input value is : ");
  Serial.println(val); // Display in serial monitor for debug
  //PORTB ^= (1<<5);
  delay(2000);
}
