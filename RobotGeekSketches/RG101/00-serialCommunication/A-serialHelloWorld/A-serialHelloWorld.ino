/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Hello World                      | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will use the Geekduino's Hardware Serial Port to send a message out to
 *  a computer (or any other device connected to the serial port).
 *  
 *  The Geekduino's hardware serial port is connected to your PC via the built in FTDI 
 *  USB to serial converter. Serial communication is also connected to hardware pins 0 and 1
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
  Serial.begin(9600);              //start the hardware serial port at a baudrate of 9600 bits per second(bps)
  Serial.println("Hello World!");  //print a message on the serial port along with a line return
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //do nothing
}//go back to the first line in loop()
