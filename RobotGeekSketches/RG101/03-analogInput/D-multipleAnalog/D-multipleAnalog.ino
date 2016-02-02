/*****************************************************************************************
 *    RG 101 - Analog Input     .--.       
 *     Multiple Analog In      |.__.|    
 *        Serial Out           ||||||    
 *                            /      \        
 *                            `._\/_.'    
 *                                                              
 *           
 *  This code will read an analog input and print out the data to the serial port
 *  
 *  The following devices can be interchanged, the list is just a guideline for the example
 *  Analog 0 - RobotGeek Knob
 *  Analog 1 - RobotGeek Slider
 *  Analog 2 - RobotGeek Light Sensor
 *  Analog 3 - RobotGeek Voltage Divider with Force Sensing Resistor
 *  Analog 6 - RobotGeek Joystick Vertical
 *  Analog 7 - RobotGeek Joystick Horizontal
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/231-analog-input-primer.html
 *  
 * Important Functions
 *  analogRead()
 *  Serial.begin()
 *  Serial.print()
 *  Serial.println()
 *****************************************************************************************/

const int ANALOG_PINS[] = {0,1,2,3,6,7};   //pin numbers for the analog input - this is 'const' since it will not change during code, and saves Arduino memory

int analogValues[6];           //holds the current analogValue

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  //analog pins do not beed to be excplicitly set via pinMode. You can set them as an INPUT, but this is not needed.

  Serial.begin(9600);          //start the serial port at a baud rate of 9600 bits per second
  Serial.println("Serial Test: Print Analog Sensor");   //write a line to the serial port
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  
  Serial.print("Analog Values:");     //print fixed text to the serial port
  for(int i = 0; i < 6; i++)
  {
    analogValues[i] = analogRead(ANALOG_PINS[i]);  //store the analog value into a variable
    delay(2); //short delay so the ADC can 'settle in'
    
    Serial.print(" A");     //print fixed text to the serial port
    Serial.print(ANALOG_PINS[i]);     //print fixed text to the serial port
    Serial.print(":");     //print fixed text to the serial port
   Serial.print(analogValues[i] );           //print a variable to the serial port
  }
  
   Serial.println("");           //print a variable to the serial port
  delay(100);                           //short delay so that the serial port doesn't go to fast.

}//go back to the first line in loop()
