int LED_PIN = 12;
void setup() {
  // I setup port 12 for out experiment.
  pinMode(LED_PIN, OUTPUT); // LED output port.
}
void ledBlink(int duration){
  /**
   * This function blinks the LED at specified port with 
   * an interval of target duration. Here, we use port 12, 
   * although arduino default port for blinking is 13
  */
  digitalWrite(LED_PIN, HIGH);
  delay(duration);
  digitalWrite(LED_PIN, LOW);
  delay(duration);
}
void sosMorse(){
  //S
  /**
  ** 1. In order to represent S, we need to use 3 'dots'. 
  *     Generally, the length of a dot is short. Here we use 1000ms 
  *     for representing a single dot. We repeat ledBlink() method 
  *     3 times with duration 1000ms.
  ** 2. In order to represent O, we need to use 3 'dash'. 
  *     Generally, the length of a dash is long. Here we use 1000ms 
  *     for representing a single dash. We repeat ledBlink() method 
  *     3 times with duration 3000ms.
  **  
  ***/
  ledBlink(1000);
  ledBlink(1000);
  ledBlink(1000);
  delay(3000); /**According to morse code convention, 
  * there should be a space between two consecutive 
  letters and to represent a single space we delay(3000). **/
  // O 
  ledBlink(3000);
  ledBlink(3000);
  ledBlink(3000);
  delay(3000);
  // S
  ledBlink(1000);
  ledBlink(1000);
  ledBlink(1000);
  //End
  delay(10000); /* delay between two SOS codes as it will continuously repeat. */
}
void loop() {
  sosMorse();
}
