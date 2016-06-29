/*****************************************************************************************
 *    RG 101 - Digital Output         |
 *    Blink without delay            -∩-
 *                                    ∏
 *                              
 *  This code will turn digital pin 13 on and off at a fixed rate. This code will also 
 *  use variables to hold the  pin number and the delay time. 
 *  This code is different from the standard blink code beccause it does not use the
 *  delay() function. Because the delay function is not used, this code is considered 
 *  non-blocking and other functions can run while mainting the blinking. However if 
 *  extra code executes slower than the desired blink rate, the actual blink rate may vary
 *    
 *  This code can blink without the delay function by using the millis() function. The   
 *  millis() function keep track of the number of milliseconds since the program started
 *  running. By checking the amount of time the program has been running, the Geekduino
 *  can toggle the LED pin at a fixed rate.
 *  
 *  This technique can be used for many different functions - for example you would use
 *  this technique to print serial debug statements at a fixed rate or update a motor
 *  without blovking the code or over-saturating the bus.
 *  
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/189-digital-output-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalWrite()
 *  millis()
 *****************************************************************************************/

//by using variables to hold the pin number and delay time, we can change out code much faster
//the use of the 'const' modifier tells the program that those variables will not change during program 
//runtime, which allows the program to store the variables in Flash memory and save valuable RAM on the 
//Geekduino/Arduino. Setting the contant variable names in all caps is not nessesary, but reccomended.
const int DIGITAL_OUT_PIN = 13;   // integer to hold the pin number that the sketch will control. 
const int BLINK_TIME = 1000;       ///the amount of time between LED 

unsigned long previousBlinkTime;  //the last time that the LED was toggles
bool ledState = HIGH;             //the state of the LED, set to HIGH to start

//setup runs once when the Geekduino/Arduino is turned on
void setup()  
{
  pinMode(DIGITAL_OUT_PIN, OUTPUT);         //set pin digitalOutputPin to be an output pin
  digitalWrite(DIGITAL_OUT_PIN, ledState);  //write the intial state to the pin

  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //the millis() function returns the number of milliseconds since the program started. This if statement checks of the difference between the current time 
  //(millis()) and the last time the LED was changed (previousBlinkTie) is greater than BLINK_TIME - if the diffference is grater, then enough time has passsed between now and the last toggle time, and it is time to toggle again
  if(millis() - previousBlinkTime >= BLINK_TIME )
  {
    ledState = !ledState; //invert the LED state, toggling it from its previous value
    digitalWrite(DIGITAL_OUT_PIN, ledState);  //write the new state to the pin
    previousBlinkTime = millis();   //set previousBlinkTime to the current time, effectivley resetting the blink time counter
  }

  //you can put any other code you want here and the LED will keep blinking. If your code takes more than BLINK_TIME to complete, you may see the LED blink at a different rate than your target rate.
}//go back to the first line in loop()
