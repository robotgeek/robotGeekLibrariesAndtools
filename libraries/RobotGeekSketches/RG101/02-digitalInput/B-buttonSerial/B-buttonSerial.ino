/*****************************************************************************************
 *    RG 101 - Digital Input     _____
 *     Serial Output            |  _  |
 *                              | |_| |
 *                              |_____| 
 *           
 *  This code print to the serial monitor when the pushbutton is pressed.
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/230-digital-input-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalRead()
 *  Serial.begin()
 *  Serial.println()
 *****************************************************************************************/

const int BUTTON_PIN = 2;   //pin number for the button - this is 'const' since it will not change during code, and saves Arduino memory

bool buttonState;           //holds the current state of the button, HIGH or LOW

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(BUTTON_PIN, INPUT);  //set button pin to input 
  Serial.begin(9600);          //start the serial port at a baud rate of 9600 bits per second
  Serial.println("Serial Test: Print Data when the Button is Pressed");   //write a line to the serial port
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  buttonState = digitalRead(BUTTON_PIN);  //reads the button (HIGH or LOW) and stores it in the buttonState variable
  
   //check if the button state is HIGH, i.e. it has been pressed
  if(buttonState == HIGH)
  {
    Serial.println("Button is being pressed!"); //write to the serial port
  }  
  
}//go back to the first line in loop()
