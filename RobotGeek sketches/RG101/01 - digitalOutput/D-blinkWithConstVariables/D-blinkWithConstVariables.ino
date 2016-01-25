/*****************************************************************************************
 *    RG 101 - Digital Output         |
 *    Blink using 'const' variables  -∩-
 *                                    ∏
 *                              
 *  This code will turn digital pin 13 on and off at a fixed rate. This code will also 
 *  use variables to hold the  pin number and the delay time. By using the 'const' keyword
 *  the variables will be sored in flash, saving RAM during the program runtime.  
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
//the use of the 'const' modifier tells the program that those variables will not change during program 
//runtime, which allows the program to store the variables in Flash memory and save valuable RAM on the 
//Geekduino/Arduino. Setting the contant variable names in all caps is not nessesary, but reccomended.
const int DIGITAL_OUT_PIN = 13;   // integer to hold the pin number that the sketch will control. 
const int DELAY_TIME = 1000;       // integer to hold the delay time in milliseconds between the digital output turning on/off. 

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
