/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Print Loop                | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will keep track of the current loop being run and print out the loop number
 *  on the Geekduino's serial port.
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

int count = 0;                    //number of loops that have been run

void setup()
{
  Serial.begin(9600);               //start the Serial port at a baud rate of 9600 bits per second (bps)
  Serial.println("Loop Counting");  //print a header one time
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  count = count + 1;          //increase the loop count by one.
  Serial.print("Loop # ");    //print the first part of the line
  Serial.println(count);      //print the value of 'count' and a line ending (println) to show the current loop
  delay(1000);                //wait for 1000ms so that we don't fill up the serial monitor too quickly.
  
}//go back to the first line in loop()





