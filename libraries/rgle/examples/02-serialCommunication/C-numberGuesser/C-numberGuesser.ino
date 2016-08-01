/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Number Guesser Game              | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will genrerate a random number and prompt you to guess the number via 
 *  the serial monitor.
 *  
 * 
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 *  Serial.begin()
 *  Serial.println()
 *  Serial.available()
 *  Serial.parseInt()
 *****************************************************************************************/

int numberToGuess = 555;      //the  number that the user is trying to guess
int userGuess;             //the last guess the user entered

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  Serial.begin(9600); //start the Serial port at a baud rate of 9600 bits per second (bps)
  
  //print prompts  
  Serial.println("Hello! Please enter a number between 0 and 1000. "); 
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //check is there are any characters incoming on the serial buffer.
  if(Serial.available() > 0)
  {
    userGuess = Serial.parseInt(); //Serial.parseInt is an advanced version of Serial.read(). Serial.parseInt() reads several characters and trys to create an integer out of them. This operation takes longer than a standard Serial.read() which just reads one character at a time
    
    Serial.print("You Guessed: ");  //print static text
    Serial.println(userGuess); //print the data that was recieved

    if(userGuess > numberToGuess)
    {
      Serial.println("You Guess is too high");  //print static text
    }    
    else if(userGuess < numberToGuess)
    {
      Serial.println("You Guess is too low");  //print static text
    }
    else if(userGuess == numberToGuess)
    {
      Serial.println("You guessed correctly!");  //print static text
    }
  }

}//go back to the first line in loop()

