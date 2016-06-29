/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Formatting                | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code displays data to the serial monitor in a variety of formats
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

  Serial.println(" ");
  Serial.println("Int");
  Serial.print("Binary:" );
  Serial.println(100, BIN);
  Serial.print("Octal:" );
  Serial.println(100, OCT);
  Serial.print("Decimal:" );
  Serial.println(100, DEC);
  Serial.print("Hexidecimal:" );
  Serial.println(100, HEX);

  Serial.println(" ");
  Serial.println("Float");

  Serial.print("0 significant Digit:" );
  Serial.println(3.14159265359, 0);
  Serial.print("1 significant Digit:" );
  Serial.println(3.14159265359, 1);
  Serial.print("5 significant Digits:" );
  Serial.println(3.14159265359, 5);

  int aInt = 'a';
  byte aByte = 'a';
  char aChar = 'a';
  Serial.println(" ");
  Serial.println("Characters 1");

  
  Serial.print("Integer " );
  Serial.println(aInt);
  Serial.print("Byte " );
  Serial.println(aByte);
  Serial.print("Character " );
  Serial.println(aChar);
  
  aInt = 97;
  aByte = 97;
  aChar = 97;
  Serial.println(" ");
  Serial.println("Characters 2");

  
  Serial.print("Integer " );
  Serial.println(aInt);
  Serial.print("Byte " );
  Serial.println(aByte);
  Serial.print("Character " );
  Serial.println(aChar);
  
  


} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //Do nothing    
}//go back to the first line in loop()





