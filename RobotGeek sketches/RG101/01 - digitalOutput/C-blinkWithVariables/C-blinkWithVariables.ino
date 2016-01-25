/*****************************************************************************************
 *    RG 101 - Digital Output   |
 *    Blink With Variables     -∩-
 *                              ∏
 *                              
 *  This code will turn digital pin 13 on and off at a fixed rate. This code will also 
 *  use variables to hold the  pin number and the delay time.  
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

//by using variables to hold the pin number and delay time, we can change out code much faster
int digitalOutputPin = 13;   //variable integer to hold the pin number that the sketch will control. 
int delayTime = 1000;      //variable integer to hold the delay time in milliseconds between the digital output turning on/off. 

//setup runs once when the Geekduino/Arduino is turned on
void setup()  
{
  pinMode(digitalOutputPin, OUTPUT);  //set pin digitalOutputPin to be an output pin
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  digitalWrite(digitalOutputPin, HIGH);     //change the pin state to HIGH, turning the pin 
  delay(delayTime);                         //wait for delayTime milliseconds (1 second). Pin stays HIGH while the geekduino waites
  digitalWrite(digitalOutputPin, LOW);      //change the pin state to HIGH, turning the pin off
  delay(delayTime);                         //wait for delayTime milliseconds (1 second) Pin stays LOW while the geekduino waits
}//go back to the first line in loop()
