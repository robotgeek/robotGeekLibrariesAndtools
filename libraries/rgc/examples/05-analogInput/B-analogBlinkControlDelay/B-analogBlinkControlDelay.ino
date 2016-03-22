/*****************************************************************************************
 *    RG 101 - Analog Input      .--.       
 *                              |.__.|    
 *        Analog Blink Control  ||||||    
 *                             /      \        
 *                             `._\/_.'    
 *                                                              
 *           
 *  This code will blink an LED on and off at a rate determined by an analog input
 *  such as a knob
 *  
 *  Analog 0 - Any Analog Input such as a RobotGeek Knob
 *  Digital 13 - Any Digital Output such as a RobotGeek LED Driver
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/231-analog-input-primer.html
 *  
 * Important Functions
 *  analogRead()
 *  digitalWrite()
 *  map()
 *****************************************************************************************/

const int ANALOG_PIN = 0;   //pin number for the analog input - 'A0' is also valid- this is 'const' since it will not change during code, and saves Arduino memory
const int LED_PIN = 13;     //pin number for the LED pin

int analogValue;           //the current analogValue
bool ledState;             //the current state of the LED
int delayTime;             //the amount of time to wait between blinks

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  //analog pins do not beed to be excplicitly set via pinMode. You can set them as an INPUT, but this is not needed.
  pinMode(LED_PIN, OUTPUT);
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogValue = analogRead(ANALOG_PIN);  //store the analog value into a variable
  delayTime = (analogValue * 5) + 100;          //convert the analog value (0-1023) to a ranage of delay times(500-10730 milliseconds)

  ledState = !ledState;              //invert the led state (HIGH goes LOW, LOW goes HIGH)
  digitalWrite(LED_PIN, ledState);   //write the value to the LED pin
  delay(delayTime);                  //wait before going to the next loop
  

}//go back to the first line in loop()
