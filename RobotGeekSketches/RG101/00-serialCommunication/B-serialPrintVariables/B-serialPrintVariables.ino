/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Print Variables           | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will use the Geekduino's Hardware Serial Port to send a message out to
 *  a computer (or any other device connected to the serial port)
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.println()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  
  int a; //integer a, automatically set to 0
  int b = 3; //integer b, manually set to 3
  int c; //intever c, automatically set to 0
  
  Serial.begin(9600);
  Serial.print("Print Variable Values: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
  
  
  Serial.println("Setting 'a' to '2' ");
  a = 2; //set variable a to 2
  Serial.print("Print # 2: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
  
  
  Serial.println("Adding 'a' and 'b' ");
  c = a + b;
  Serial.print("Print # 3: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //Do nothing    
}//go back to the first line in loop()





