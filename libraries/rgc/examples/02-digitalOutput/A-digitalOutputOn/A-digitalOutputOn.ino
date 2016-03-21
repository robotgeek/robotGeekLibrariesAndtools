/*****************************************************************************************
 *    RG 101 - Digital Output   |
 *    Digital Output On        -∩-
 *                              ∏
 *                              
 *  This code will turn digital pin 13 on
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/189-digital-output-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalWrite()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(13, OUTPUT);      //set pin 13 to be an output pin
  digitalWrite(13, HIGH);   //set the state of pin 13 to HIGH, turning the pin on / setting it to 5 v
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //do nothing
}//go back to the first line in loop()
