/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     Fade     _____________                         _____________
 *             |             |                       |             | 
 *             |             |                       |             | 
 *     ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will fade an LED using Pulse-width modulation
 *  
 *  Digital 3 - RobotGeek LED
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/232-pwm-primer.html
 *  
 *  This code is based of the stnadard Arduino fade code
 *  https://www.arduino.cc/en/Tutorial/Fade
 *  
 * Important Functions
 *  analogWrite()
 *****************************************************************************************/

const int LED_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int FADE_AMOUNT = 5; //amount to fade by - lower values create a more incremental, slower fade

int pwmValue;           //holds the current PWM value (0-255)\

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT); //set LED_PIN to be an output
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //analogWrite sets LED_PIN to whatever value is in PWMValue  
  //This can be a value between 0 and 255. 0 is 0% duty cycle (off) and 255 is 100% duty cycle(on).
  //Values inbetween represent fractions of that duty cycle (i.e. 128 is ~50%). 
  //NOTE - AnalogWrite does not create a 'true' analog value, but a PWM value   
  analogWrite(LED_PIN, pwmValue);  

  pwmValue = pwmValue + FADE_AMOUNT; //change the PWMValue for the next loop

  //if the PWM value gets to or higher than 255
  if(pwmValue >= 255)
  { 
    pwmValue = 0; //reset the value back to 0
  }

  delay(50);  //wait 50 milliseconds to slow down the fading so that it is easy to see

  
}//go back to the first line in loop()
