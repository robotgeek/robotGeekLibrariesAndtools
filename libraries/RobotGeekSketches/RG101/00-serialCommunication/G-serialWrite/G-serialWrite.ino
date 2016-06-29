/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Write                     | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code uses the Serial.write() function to send individual bytes on the serial port.
 *  Serial.write() is often used when the Geekduino is going to communicate with another
 *  microcontroller or directly to a computer. By sending values as individual bytes, it 
 *  is possible to send numeric data in much smaller packets, making the communications
 *  much more efficient. 
 *    
 *
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 * http://learn.robotgeek.com/getting-started/250-ascii.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.write()
 *****************************************************************************************/

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  
  Serial.begin(9600);
  Serial.write('M');
  Serial.write('e');
  Serial.write('s');
  Serial.write('s');
  Serial.write('a');
  Serial.write('g');
  Serial.write('e');
  Serial.write('1');
  Serial.write('2');
  Serial.write('3');
  Serial.write(1);
  Serial.write(2);
  Serial.write(3);
  Serial.write('.');
  
  delay(1000);
  
  for(int i=32; i<128; i++)
  {
    Serial.write(i);
  }
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //Do nothing    
}//go back to the first line in loop()





