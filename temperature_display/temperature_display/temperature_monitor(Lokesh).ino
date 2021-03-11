/**
** A simple program to read ambient temperature
** and display it in deg.F on the LCD display monitor
*/
/** Initialize the library by associating any needed LCD interface pin*/
#include <LiquidCrystal.h>
/***Arduino pin number to establish connection between arduino and LCD display**/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
/**Establish connection arduino and LCD display**/
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/**Required variable decleration**/
float temperatureValue;
float sensorValue;
double degF = 0.0;
/***Initialize pin number to read temperature sensor value**/
const int SENSOR_PIN = 0;

void setup() {
  /**Initialize the LCD's columns and rows*/
  lcd.begin(16,2);
  lcd.print("Temp. (deg. F):"); /* write message on display*/
  Serial.begin(9600); /*serial monitor communcation number to get console output*/
}
/**
 * Loop and setup method automatically gets calls from the ardunio board.
 * However, setup function gets call only once while loop will continue forever
*/
void loop() {
  lcd.clear(); /***Clear LCD display what already have on the display**/
  /**Read ambient temperature as an analogy input and convert it 0-5**/
  sensorValue = (analogRead(SENSOR_PIN)/1024.0)*5.0;
  Serial.print( "Voltage: ");
  Serial.print(sensorValue);
  temperatureValue = (sensorValue-0.5)*100.0;
  Serial.print( " Deg. C: ");
  Serial.print(temperatureValue);
  degF = temperatureValue*(9.0/5.0) + 32.0; /** convert into fahrenheit from celcious*/
  Serial.print( " Deg. F: ");
  Serial.println(degF);
  delay(100); /* delay of 100ms*/
  lcd.print("Temp. (deg.F) :"); /* display message on LCD's display*/
  lcd.setCursor(0,1); /**Move cursor to at the beginning of 2nd row at LCD display*/
  lcd.print(degF); /** display deg in F in the LCD display*/
  delay(500); /** 500ms delay between to messages*/
  

}
