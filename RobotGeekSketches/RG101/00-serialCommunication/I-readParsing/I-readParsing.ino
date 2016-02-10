/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Print Variables           | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will use Arduino's serial functions to easily parse integers and floats
 *  from a standard serial input.
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.println()
 *  Serial.parseInt()
 *  Serial.parseFloat()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  int inputInt;
  float inputFloat;
  
  Serial.begin(9600);
  Serial.println("Enter a number between -32768 and 32767");

  while(Serial.available() <= 0)
  {
     //wait for serial data
  }

  inputInt = Serial.parseInt();
  
  Serial.println("Enter a floating point number (i.e. 3.14)");

  while(Serial.available() <= 0)
  {
     //wait for serial data
  }

  inputFloat = Serial.parseFloat();

  Serial.print("You entered an integer: ");
  Serial.print(inputInt);
  Serial.print(" and a floating point: ");
  Serial.println(inputFloat);
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //Do nothing    
}//go back to the first line in loop()





