/*****************************************************************************************
 *    RG 101 - Digital Input     _____
 *     Direct Button            |  _  |
 *                              | |_| |
 *                              |_____| 
 *           
 *  This code will read a pushbutton with resistor attached to digital pin 2 and 
 *  turn on digital pin 3 whenever the button is pressed.
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/230-digital-input-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalRead()
 *  digitalWrite()
 *****************************************************************************************/
//uncomment the follwoing line to enable the use of the Interbal Pullup
//#define USE_PULLUP true

//use #ifdef to check for a #define, and set #defines based on the results 
#ifdef USE_PULLUP
  #define BUTTON_PIN_MODE INPUT_PULLUP
  #define INVERT_BUTTON_LOGIC true
#else
  #define BUTTON_PIN_MODE INPUT
  #define INVERT_BUTTON_LOGIC false
#endif
  

const int BUTTON_PIN = 2;   //pin number for the button - this is 'const' since it will not change during code, and saves Arduino memory
const int LED_PIN = 3;      //pin number for the LED - this is 'const' since it will not change during code, and saves Arduino memory

bool buttonState;           //holds the current state of the button, HIGH or LOW

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(BUTTON_PIN, BUTTON_PIN_MODE);  //set button pin to input 
  pinMode(LED_PIN, OUTPUT);    //set led pin to output 
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  buttonState = digitalRead(BUTTON_PIN);  //reads the button (HIGH or LOW) and stores it in the buttonState variable
  
  if(INVERT_BUTTON_LOGIC ==true)
  {
    digitalWrite(LED_PIN, !buttonState); 
  }
  else
  {
    digitalWrite(LED_PIN, buttonState); 
  }
  
}//go back to the first line in loop()
