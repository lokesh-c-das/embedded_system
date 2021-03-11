// Multiple interrupt enable levels
// 1. Connect timer to event:  For example, overflow or counter match --> May need to prescale the clock...Let's assume we are using tcnt0
// 2. Connnect event to  flag register.
// 3. Connect flag to interrupt system
// 4. Enable interrupt system.
//
// Applicable Registers:
// TIFR0 - INTERRTUPT FLAG REGTISTER: TIMER COUTNER INTERRRUPT FLAG REGISTER...Pg 88
// - - - - - OCF0B OCF0A TOVO

// TIMSK0 - INTERRUPT MASK REGISTER : ENABLE OUTPUT COMPARE AND OVERFLOW ERROR Pg. 88
// - - - - - OCIE0B OCIE0A TOIE0

// OCR0A  - OUTPUT COMPARE REGISTER
// OCROB  OUTPUT COMPARE RESITER

// TCCROA - TIMER COUNTER CONTROL REGISTER A (COMPARE OUTPUT MATCH AB/ WAVEFORM GENERATOR MODE COMA,WGM) ...PG 84
// COM0A1 COM0A0  COM0B1 COM0B0 - - WGM01 WGM00

// TCCROB - TIMER COUNTER COUNTROL REGISTER B (FORCE OUTPUT COMPARE REGISTER BITS, CLOCK SELECT BITS--PRESCALE FOR TIMERS)
// FOC0A FOC0B - - WGM02 CSO2 CS01 CS00

// TCNT0  - TIMER COUNTER  REGISTER

// TIMER COUNTER INPUT CAPTURE... CAPTURE AN INPUT EVENT AND GIVE IT A TIME STAMP INDICATING TIME OF OCCURENCE
// INPUT CAPTURE --> USE TCNT1 (16 bit counter register)

// i BIT IN THE STATUS REGISTER...<--
//
// TCCR1A: COM1A1 COM1A0 COM1B1 COM1B0 - - WGM11 WGM10 (PG 108/110)  --> Input capture edge select, waveform generator  mode, clock select
// TCCR1B ICNC1 ICES1 - WGM13 WGM12 CS12 CS11 CS10
// TCCR1C : FOC1A FOC1B - - - - - -

// TIMSK1 (PAGE 112)
// - - ICIE1 - - OCIE1B OCIE1A TOIE1

// DDRB: DATA DIRECTION REGISTER FOR PORT B (PAGE 72)  --> REFERENCE FOR WHICH PORT MAPS TO WHAT ON ARDUINO...
// DDB7 DDB6 DDB5 DDB4 DDB3 DDB2 DDB1 DDB0

//   ************  PORT MAPPINGS   *****************    
//
// Digital pins:
// Pins 0 – 7: PORT D [0:7]
// Pins 8 – 13: PORT B [0:5]
// Pins 14 – 19: PORT C [0:5] (Arduino analog pins 0 – 5)
// digital pins 0 and 1 are RX and TX for serial communication
// digital pin 13 connected to the base board LED

//  ***********  PORT MAPPINGS for pin change interrupts
// PCINT[23:0] – any signal change (toggle)
// PCINT[7:0] – PORT B [7:0]
// PCINT[14:8] – PORT C [6:0]
// PCINT[23:16] – PORT D [7:0]

// PCMSK0 : PIN CHANGE MASK REGISTER 0 ; Selects whether pin change interrupt is enabled on the corresponding I/O pin..
// PCINT7 - PCINT0

//PCICR: PIN CHANGE INTERRUPT CONTROL REGISTER
// - - - - - PCIE2 PCIE1 PCIE0
// PCIE2 --> 23 - 16
// PCIE1 --> 15 - 8
// PCIE0 --> 7 - 0

// DDRB PAGE 280  <--REGISTER SUMMARY....STARTS ON 275 - 280



#include <avr/interrupt.h>
#include <avr/sleep.h>

int inPin = 10; // Pushbutton connected to pin 10
int val = 0; // variable to store the input value read;
int val2 = 0;
int ovfCnt = 0; // Let's count the number of counter overflows
int butPushed = 0; //


void setup() {
  cli();  // Disable the int
  
  // Set the Pin 13 as output and 10 as input :  Writing a 1 makes output...0 makes input
  DDRB |=(1<<5);
  DDRB &=~(1<<2);
  

  // Control regs for Timer 1, disable unless sw press
  TCCR1A =  0b000000;
  TCCR1B = 0b00000101;
  TIMSK1 = (1<<TOIE1); // Enable TIME overflow

  // ENABLE THE INTERRUPT BUT DO NOT CONNECT TCNT1 TO A SOURCE

  // Control regs for PCI
  PCICR = 0b00000001;
  PCMSK0 = 0b00000100;
  
  // Set the LED to OFF
  PORTB &= ~(1<<5);
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


  if (ovfCnt == 0) {
    // Cut the light on and set the count for 3 seconds.
    PORTB |= (1 << 5); 
    TCNT1 = 0x48E4;
    ovfCnt = 1;
  } else {
    // Cut the light off, disable the timer counter
    PORTB &= ~(1 << 5);
    TCCR1B = 0x00;  // Disconnect the source for TCNT1
    ovfCnt = 0;
  }
  Serial.print("state:");
  Serial.print(ovfCnt);

}


void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(inPin);
  Serial.print("The input value is : ");
  Serial.println(val); // Display in serial monitor for debug
  //PORTB ^= (1<<5);
  delay(2000);

  
}
