int LED_PIN = 12;
String inputValue = "";
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, HIGH);
  Serial.println("Setup Done.");
}
void ledBlink(String ledSeq){
  for(int i=0;i<ledSeq.length();i++){
    if(ledSeq[i]=='0'){
      digitalWrite(LED_PIN,HIGH);
      delay(1000);
      digitalWrite(LED_PIN,LOW);
      delay(1000);
    }else{
      digitalWrite(LED_PIN,HIGH);
      delay(3000);
      digitalWrite(LED_PIN,LOW);
      delay(3000);
    }
  }
}
void callBlink(char c){
  /*
  ** 0 - dot
  ** 1 - dash
  **/
  switch(c){
    case 'A': ledBlink("01"); break;
    case 'B': ledBlink("1000"); break;
    case 'C': ledBlink("1010"); break;
    case 'D': ledBlink("100"); break;
    case 'E': ledBlink("0"); break;
    case 'F': ledBlink("0010"); break;
    case 'G': ledBlink("110"); break;
    case 'H': ledBlink("0000"); break;
    case 'I': ledBlink("00"); break;
    case 'J': ledBlink("0111"); break;
    case 'K': ledBlink("101"); break;
    case 'L': ledBlink("0100"); break;
    case 'M': ledBlink("11"); break;
    case 'N': ledBlink("10"); break;
    case 'O': ledBlink("111"); break;
    case 'P': ledBlink("0110"); break;
    case 'Q': ledBlink("1101"); break;
    case 'R': ledBlink("010"); break;
    case 'S': ledBlink("000"); break;
    case 'T': ledBlink("1"); break;
    case 'U': ledBlink("001"); break;
    case 'V': ledBlink("0001"); break;
    case 'W': ledBlink("011"); break;
    case 'X': ledBlink("1001"); break;
    case 'Y': ledBlink("1011"); break;
    case 'Z': ledBlink("1100"); break;
    case '0': ledBlink("11111"); break;
    case '1': ledBlink("01111"); break;
    case '2': ledBlink("00111"); break;
    case '3': ledBlink("00011"); break;
    case '4': ledBlink("00001"); break;
    case '5': ledBlink("00000"); break;
    case '6': ledBlink("10000"); break;
    case '7': ledBlink("11000"); break;
    case '8': ledBlink("11100"); break;
    case '9': ledBlink("11110"); break;
    default: break;
      
  }
}
void parseMorseCode(String mCode){
  /**This method will read every character from the input string**/
  for(int i=0;i<mCode.length();i++){
    callBlink(mCode[i]);
    delay(3000);
    Serial.println(mCode[i]);
  }
}
void generalizedMorse(){
  /** This method will read input from the user and 
  **  and send it to parseMorseCode method
  */
  while(Serial.available()){
    inputValue = Serial.readString();
    parseMorseCode(inputValue);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  generalizedMorse();

}
