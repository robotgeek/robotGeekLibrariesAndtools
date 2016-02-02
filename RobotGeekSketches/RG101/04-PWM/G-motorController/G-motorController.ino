/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     Motor           _____________                         _____________
 *     Control        |             |                       |             | 
 *                    |             |                       |             | 
 *            ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will control a single motor attached to a 1A Dual TB6612FNG Motor Driver 
 *  or similar motor driver.
 *  
 *  Digital 2 - AIN1 (direction bit 1)
 *  Digital 4 - AIN2 (direction bit 2)
 *  Digital 3 - PWMA (PWM speed control
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/232-pwm-primer.html
 *  
 *  
 * Important Functions
 *  analogWrite()
 *****************************************************************************************/

const int PWM_PIN_A = 3;      //pin number for the PWM speed output - this is 'const' since it will not change during code, and saves Arduino memory
const int DIRECTION_1_A = 2;  //pin number for the direction bit 1 output - this is 'const' since it will not change during code, and saves Arduino memory
const int DIRECTION_2_A = 4;  //pin number for the direction bit 2 output - this is 'const' since it will not change during code, and saves Arduino memory

int pwmValue;           //holds the current PWM value (0-255)\

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(PWM_PIN_A, OUTPUT); //set LED_PIN to be an output
  pinMode(DIRECTION_1_A, OUTPUT); //set LED_PIN to be an output
  pinMode(DIRECTION_2_A, OUTPUT); //set LED_PIN to be an output

  //make sure the motor is stopped
  digitalWrite(DIRECTION_1_A, LOW); //set the direction bit low
  digitalWrite(DIRECTION_2_A, LOW); //set the direction bit low
  analogWrite(PWM_PIN_A, 0);        //set speed to 0
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{  

  //start CW rotation
  digitalWrite(DIRECTION_1_A, HIGH); //set the direction bit low
  digitalWrite(DIRECTION_2_A, LOW); //set the direction bit low
 
  //ramp up speed
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(PWM_PIN_A, i);        //set speed to 0
    delay(100);
  }
  //ramp down speed
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(PWM_PIN_A, i);        //set speed to 0
    delay(100);
  }
  

  //start CCW rotation
  digitalWrite(DIRECTION_1_A, LOW); //set the direction bit low
  digitalWrite(DIRECTION_2_A, HIGH); //set the direction bit low
 
  //ramp up speed
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(PWM_PIN_A, i);        //set speed to 0
    delay(100);
  }
  //ramp down speed
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(PWM_PIN_A, i);        //set speed to 0
    delay(100);
  }
  
  
  
}//go back to the first line in loop()
