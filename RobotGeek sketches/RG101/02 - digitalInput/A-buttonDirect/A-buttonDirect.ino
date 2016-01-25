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

const int BUTTON_PIN = 2;   //pin number for the button - this is 'const' since it will not change during code, and saves Arduino memory
const int LED_PIN = 4;      //pin number for the LED - this is 'const' since it will not change during code, and saves Arduino memory

bool buttonState;           //holds the current state of the button, HIGH or LOW

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(BUTTON_PIN, INPUT);  //set button pin to input 
  pinMode(LED_PIN, OUTPUT);    //set led pin to output 
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  buttonState = digitalRead(BUTTON_PIN);  //reads the button (HIGH or LOW) and stores it in the buttonState variable
  digitalWrite(LED_PIN, buttonState);     //write the button state to the LED state.
}//go back to the first line in loop()
