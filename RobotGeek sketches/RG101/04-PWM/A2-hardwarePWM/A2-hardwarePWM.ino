/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     Hardwar  _____________                         _____________
 *     PWM     |             |                       |             | 
 *             |             |                       |             | 
 *     ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will set a PWM cycle analgoWrite(). 
 *  
 *  Digital 3 - RobotGeek LED
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our PWM Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/232-pwm-primer.html
 *  
 *  This code is based of the stnadard Arduino fade code
 *  https://www.arduino.cc/en/Tutorial/Fade
 *  
 * Important Functions
 *  analogWrite()
 *****************************************************************************************/

const int PWM_LED1 = 5;
const int PWM_LED2 = 6;

const int PWM_VAL_1 = 128;
const int PWM_VAL_2 = 255;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(PWM_LED1, OUTPUT); //set LED_PIN to be an output
  pinMode(PWM_LED2, OUTPUT); //set LED_PIN to be an output
 
 //analogWrite sets LED_PIN to whatever value is in PWMValue  
  //This can be a value between 0 and 255. 0 is 0% duty cycle (off) and 255 is 100% duty cycle(on).
  //Values inbetween represent fractions of that duty cycle (i.e. 128 is ~50%). 
  //NOTE - AnalogWrite does not create a 'true' analog value, but a PWM value   
  analogWrite(PWM_LED1, PWM_VAL_1); //set the static LED pin high as a control
  analogWrite(PWM_LED2, PWM_VAL_2); //set the static LED pin high as a control
   
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{

  
}//go back to the first line in loop()
