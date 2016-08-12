/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Print Variables           | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will use the Geekduino's Hardware Serial Port to send a message out to
 *  a computer (or any other device connected to the serial port). This example will
 *  show how to output the current values of variables instead of static text
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.print()
 *  Serial.println()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  
  int a = 0;  //integer a, manually set to 0
  int b = 3;  //integer b, manually set to 3
  int c ;     //intever c, automatically set to 0
  
  Serial.begin(9600);                         //start the hardware serial port at a baudrate of 9600 bits per second(bps)
  Serial.println("   ");                      //print empty line
  Serial.println("**********************************************************************");  
  Serial.println("**********************************************************************");
  Serial.println("   ");                      //print empty line
  //Serial.println("PRINT VARIABLES : ");  //print static text
  Serial.println("   ");                      //print empty line
  Serial.println("INITIAL VALUES: ");         //print static text
  //Serial.print("PRINT # 1: ");                //print static text
  Serial.print("a = ");                       //print static text
  Serial.print(a);                            //print the value in variable a
  Serial.print(" b = ");                      //print static text
  Serial.print(b);                            //print the value in variable b
  Serial.print(" c = ");                      //print static text
  Serial.println(c);                          //print the value in variable c
  Serial.println("   ");                      //print empty line

  Serial.println("ADD 'a' AND 'b' ");      //print static text

  c = a + b;                                  //set c to the value of a and b added
  
  //Serial.print("Print # 3: ");                //print static text
  Serial.print("a = ");                       //print static text
  Serial.print(a);                            //print the value in variable a
  Serial.print(" b = ");                      //print static text
  Serial.print(b);                            //print the value in variable b
  Serial.print(" c = ");                      //print static text
  Serial.println(c);                          //print the value in variable c
  Serial.println("   ");                      //print empty line

  
  Serial.println("CHANGE 'a' TO '2' ");      //print static text
  a = 2;                                      //set variable a to 2
  //Serial.print("PRINT # 2: ");                //print static text
  Serial.print("a = ");                       //print static text
  Serial.print(a);                            //print the value in variable a
  Serial.print(" b = ");                      //print static text
  Serial.print(b);                            //print the value in variable b
  Serial.print(" c = ");                      //print static text
  Serial.println(c);                          //print the value in variable c
  Serial.println("   ");                      //print empty line
  
  
  Serial.println("ADD 'a' AND 'b' ");      //print static text
  c = a + b;                                  //set c to the value of a and b added
  //Serial.print("Print # 3: ");                //print static text
  Serial.print("a = ");                       //print static text
  Serial.print(a);                            //print the value in variable a
  Serial.print(" b = ");                      //print static text
  Serial.print(b);                            //print the value in variable b
  Serial.print(" c = ");                      //print static text
  Serial.println(c);                          //print the value in variable c
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //Do nothing    
}//go back to the first line in loop()





