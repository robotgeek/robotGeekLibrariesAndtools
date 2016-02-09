/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Serial Without Delay             | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                              
 *  This code will print a serial message at a fixed rate without the use of delay().  
 *  Because the delay function is not used, this code is considered non-blocking and 
 *  other functions can run while maintaining the serial output.  
 *  However if extra code executes slower than the desired blink rate, the
 *  actual blink rate may vary
 *    
 *  This code can blink without the delay function by using the millis() function. The   
 *  millis() function keep track of the number of milliseconds since the program started
 *  running. By checking the amount of time the program has been running, the Geekduino
 *  can toggle the LED pin at a fixed rate.
 *  
 *  This technique can be used for many different functions - for example you would use
 *  this technique to blink an LED  at a fixed rate or update a motor
 *  without blocking the code or over-saturating the bus.
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.println()
 *  millis() 
 *****************************************************************************************/


//by using variables to hold the pin number and delay time, we can change out code much faster
//the use of the 'const' modifier tells the program that those variables will not change during program 
//runtime, which allows the program to store the variables in Flash memory and save valuable RAM on the 
//Geekduino/Arduino. Setting the contant variable names in all caps is not nessesary, but reccomended.
const int PRINT_TIME = 1000;       ///the amount of time between Serial prints

unsigned long previousBlinkTime;  //the last time that the serial statement was printed
int count = 0;                    //number of loops

//setup runs once when the Geekduino/Arduino is turned on
void setup()  
{
  Serial.begin(9600);
  Serial.println("Loop Counting");
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //the millis() function returns the number of milliseconds since the program started. This if statement checks of the difference between the current time 
  //(millis()) and the last time the LED was changed (previousBlinkTie) is greater than BLINK_TIME - if the diffference is grater, then enough time has passsed between now and the last toggle time, and it is time to toggle again
  if(millis() - previousBlinkTime >= PRINT_TIME )
  {
    previousBlinkTime = millis();   //set previousBlinkTime to the current time, effectivley resetting the blink time counter
    
    count = count + 1;                  //increase the loop count by one.
    Serial.print("Loop # ");            //print the first part of the line
    Serial.print(count);                //print the value of 'count' to show the current loop
    Serial.print(" at ");                //print text
    Serial.println(previousBlinkTime);  //print the current value of 'previousBlinkTime' and a line ending (println) to show the time of the print statement
  }

  //you can put any other code you want here and the serial data will keep printing.. If your code takes more than PRINT_TIME to complete, you may see the LED blink at a different rate than your target rate.
}//go back to the first line in loop()
