/*****************************************************************************************
 *    RG 101 - Digital Output   |
 *    Blink Basic              -∩-
 *                              ∏
 *                              
 *  This code will turn digital pin 13 on and off at a fixed rate. 
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/189-digital-output-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalWrite()
 *  delay()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(13, OUTPUT);      //set pin 13 to be an output pin
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  digitalWrite(13, HIGH);     //change the pin state to HIGH, turning the pin on
  delay(1000);                //wait for 1000 milliseconds (1 second). Pin 13 stays HIGH while the geekduino waits
  digitalWrite(13, LOW);      //change the pin state to HIGH, turning the pin off
  delay(1000);                //wait for 1000 milliseconds (1 second) Pin 13 stays LOW while the geekduino waits
}//go back to the first line in loop()
