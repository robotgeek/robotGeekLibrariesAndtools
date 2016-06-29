/*****************************************************************************************
 *    RG 101 - Pulse-Width Modulation (PWM)
 *     AnalogIn        _____________                         _____________
 *     PWM Out        |             |                       |             | 
 *                    |             |                       |             | 
 *            ________|             |_______________________|             |_______________________                                                 
 *           
 *  This code will set the brightness of an LED based on ana analog input
 *  
 *  Digital 3 - RobotGeek LED
 *  Analog 0 - Robotgeek Knob or other Analog Sensor
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/232-pwm-primer.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  analogWrite()
 *  map()
 *****************************************************************************************/

const int ANALOG_PIN = 0;
const int LED_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory

int analogSensorValue;   //the raw value read from the analog sensor
int pwmValue;           //holds the current PWM value (0-255)\

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT); //set LED_PIN to be an output
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 
  
  //the map functions converts a number from one range to another, thus 'mapping' the value.
  //the map syntax is as follows:
  //    map(input, inputLow, inputHigh, outputLow, outputHigh);
  //So in this example, the 'analogSensorValue' is mapped from it's Low/High values (0-1023) to the PWM output values (0-255)
  //'0' is mapped to '0', '512' is mapped to 128', '1023' is mapped to '255'
  pwmValue = map(analogSensorValue, 0, 1023, 0, 255);
   
  analogWrite(LED_PIN, pwmValue);   //set LED_PIN to whatever value is in pwmValue, thus adjusting the LED based on the analog sensor  

  
}//go back to the first line in loop()
