/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     Manual   _____________                         _____________
 *     PWM     |             |                       |             | 
 *             |             |                       |             | 
 *     ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will set a PWM cycle using only delays. This code is for demonstration purposes
 *  only.
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
 *  
 *****************************************************************************************/

const int PWM_LED = 3;
const int STATIC_LED = 5;

const int CYCLE_TIME = 1000;
const int ON_TIME = 900;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(PWM_LED, OUTPUT); //set LED_PIN to be an output
  pinMode(STATIC_LED, OUTPUT); //set LED_PIN to be an output

  digitalWrite(STATIC_LED, HIGH); //set the static LED pin high as a control
   
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{

  digitalWrite(PWM_LED, HIGH);
  delayMicroseconds(ON_TIME); 
  
  digitalWrite(PWM_LED, LOW); 
  delayMicroseconds(CYCLE_TIME - ON_TIME); 

  
}//go back to the first line in loop()
