/*****************************************************************************************
 *    RG 101 - Digital Output    |
 *    Blink Using Defines       -∩-
 *                               ∏
 *                              
 *  This code will turn digital pin 13 on and off at a fixed rate. This code will also 
 *  use #defines to hold the  pin number and the delay time.  
 *  
 *  NOTE: #defines are generally not reccomended to be used for numerical data - if
 *  you can use a 'const' variable, you should do so. The follwoing code is intended
 *  as a general introduction to #defines. 
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

//by using #define  to hold the pin number and delay time, we can change out code much faster
//use of the #define  directive allows the pre-processor to quickly replace all references of
// the #define  with its value. This has the exact same effect on memoery as if you hardcoded the 
//#define  values into the code. #define names in all caps is not nessesary, but reccomended.
#define DIGITAL_OUT_PIN  13   // #define to hold the pin number that the sketch will control. 
#define DELAY_TIME  1000       // #define  to hold the delay time in milliseconds between the digital output turning on/off. 

//setup runs once when the Geekduino/Arduino is turned on
void setup()  
{
  pinMode(DIGITAL_OUT_PIN, OUTPUT);   //set pin digitalOutputPin to be an output pin
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  digitalWrite(DIGITAL_OUT_PIN, HIGH);     //change the pin state to HIGH, turning the pin 
  delay(DELAY_TIME);                         //wait for delayTime milliseconds (1 second). Pin stays HIGH while the geekduino waites
  digitalWrite(DIGITAL_OUT_PIN, LOW);      //change the pin state to HIGH, turning the pin off
  delay(DELAY_TIME);             
}//go back to the first line in loop()
