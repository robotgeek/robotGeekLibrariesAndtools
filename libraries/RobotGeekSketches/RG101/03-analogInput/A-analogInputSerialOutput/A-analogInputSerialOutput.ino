/*****************************************************************************************
 *    RG 101 - Analog Input     .--.       
 *     Analog In               |.__.|    
 *        Serial Out           ||||||    
 *                            /      \        
 *                            `._\/_.'    
 *                                                              
 *           
 *  This code will read an analog input and print out the data to the serial port
 *  
 *  Analog 0 - Any Analog Input such as a RobotGeek Knob
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

const int ANALOG_PIN = 0;   //pin number for the analog input - this is 'const' since it will not change during code, and saves Arduino memory

int analogValue;           //holds the current analogValue
float analogVoltage;             //voltage value
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
  analogValue = analogRead(ANALOG_PIN);       //store the analog value into a variable
  analogVoltage = 5.0 * (analogValue/1023.0); //convert analog value to a 0-5v voltage
   
  Serial.print("Analog Value:");         //print fixed text to the serial port
  Serial.print(analogValue);           //print a variable to the serial port
  Serial.print(" Voltage:");              //print fixed text to the serial port
  Serial.println(analogVoltage);           //print a variable to the serial port
  delay(100);                            //short delay so that the serial port doesn't go to fast.

}//go back to the first line in loop()
