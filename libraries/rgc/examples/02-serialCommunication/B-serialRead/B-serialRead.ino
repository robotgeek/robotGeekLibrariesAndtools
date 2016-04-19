/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Read                      | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will read data from the serial port and echo it back to the serial port.
 *  
 *  Serial data is buffered on the Geekduino's chip and must be read in byte by byte.
 *
 *  This is a very basic demo of readinf data - there are many functions and ways to 
 *  read data.
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
  Serial.begin(9600);                                               //start the Serial port at a baud rate of 9600 bits per second (bps)
  Serial.println("Type a single letter or number and press enter"); //print a header one time
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //check is there are any characters incoming on the serial buffer.
  if(Serial.available() > 0)
  {
    incomingData = Serial.read(); //read one character from the serial buffer and remove that character from the buffer
    Serial.print("You Typed: ");  //print static text
    Serial.println(incomingData); //print the data that was recieved
    
  }
  
}//go back to the first line in loop()





