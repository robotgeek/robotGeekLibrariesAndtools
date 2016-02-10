/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Software Serial                  | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will start a software serial instance on pins 10/11 as well as a hardware
 *  serial port. It will connect the two serial ports so that input from the hardware
 *  port is sent as output on the software serial port and vice versa.
 *  
 *  Software serial is not as reliable as hardware serial, and should be used
 *  sparingly and at lower speeds. 
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
 *  Serial.write()
 *****************************************************************************************/

#include <SoftwareSerial.h>


SoftwareSerial swSerial(10, 11); //start software class RX-10, TX-11

char incomingData;  //create an empty chracter variable to hold the incoming data

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  Serial.begin(9600);
  Serial.println("Print Message to Hardware Serial");

  
  swSerial.begin(4800);
  swSerial.println("Print Message to Software Serial");

  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //check if there is data on the Hardware Serial port and if so print it to the Software serial port
  if (Serial.available()) 
  {
    swSerial.write(Serial.read());
  }


  //check if there is data on the Software Serial port and if so print it to the Hardware serial port
  if (swSerial.available()) 
  {
    Serial.write(swSerial.read());
  }
  
}//go back to the first line in loop()





