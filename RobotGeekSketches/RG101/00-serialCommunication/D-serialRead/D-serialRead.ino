/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Hello World                      | >_   |   
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
 *  Serial.available()
 *  Serial.read()
 *****************************************************************************************/


char incomingData;  //create an empty chracter variable to hold the incoming data

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  Serial.begin(9600);
  Serial.println("Type a single letter or number and press enter");
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  if(Serial.available() > 0)
  {
    incomingData = Serial.read();
    
     Serial.print("You Typed: ");
     Serial.println(incomingData);
    
  }
  
}//go back to the first line in loop()





