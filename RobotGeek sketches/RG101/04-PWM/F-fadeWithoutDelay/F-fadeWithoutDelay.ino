/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     Fade            _____________                         _____________
 *     Without        |             |                       |             | 
 *     Delay          |             |                       |             | 
 *            ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will fade an LED up and down using Pulse-width modulation and millis() to
 *  avoid delays
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

int pwmValue;           //holds the current PWM value (0-255)
int fadeAmount = 5;     //amount to fade by - lower values create a more incremental, slower fade
unsigned long lastFadeChange;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT); //set LED_PIN to be an output
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  if(millis() - lastFadeChange > 50)
  {
    lastFadeChange = millis();        //reset the counter
    analogWrite(LED_PIN, pwmValue);   // sets LED_PIN to whatever value is in PWMValue  
    pwmValue = pwmValue + fadeAmount; //change the PWMValue for the next loop
  
    //if the PWM value gets to/higher than 255 or to/lower than 0
    if(pwmValue >= 255 || pwmValue <= 0)
    { 
      fadeAmount = -1 * fadeAmount; //reverse the fade amount so the fade goes in the other direction 
    }
  }
  


  
}//go back to the first line in loop()
