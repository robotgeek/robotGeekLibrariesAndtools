/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Number Guesser Game              | >_   |   
 *         With LED Output             |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will genrerate a random number and prompt you to guess the number. If the
 *  user guesses the correct number, the LED will blink and turn on.
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
 *  Serial.read()
 *  Serial.parseInt()
 *  Serial.readString()
 *  random()
 *  digitalWrite()
 *****************************************************************************************/

const int LED_PIN = 13; //pin for the LED driver

int randomNumberToGuess;      //the random number that the user is trying to guess
int userGuess;             //the last guess the user entered

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT);   //set LED as an output
  digitalWrite(LED_PIN, LOW); //turn the LED off

  Serial.begin(9600);                                               //start the Serial port at a baud rate of 9600 bits per second (bps)
  randomNumberToGuess = random(1001);   //generate a 'random' number.
  //randomNumberToGuess = random(1001); //everytime you call random() a new random number is picked. Try calling random() multiple times by uncommenting this line
  //randomNumberToGuess = random(1001);   
  
  //uncomment the next 2 lines if you want to see the random number for debugging
  //Serial.print("Random Number: "); 
  //Serial.println(randomNumberToGuess); 
  
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

    //check if the number the user guessed is more than the number to guess - if it is, then tell the user by printing a message
    if(userGuess > randomNumberToGuess)
    {
      Serial.println("You Guess is too high");  //print static text
    }    
    
    //if not, check if the number the user guessed is less than the number to guess - if it is, then tell the user by printing a message
    else if(userGuess < randomNumberToGuess)
    {
      Serial.println("You Guess is too low");  //print static text
    }
    
    //if not, check if the number the user guessed is equal to the number to guess - if it is, then tell the user by printing a message
    else if(userGuess == randomNumberToGuess)
    {
      Serial.println("You guessed correctly!");  //print static text
      
      //flash the LED on/off twice, ending with the LED on.
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
      digitalWrite(LED_PIN, HIGH);
    }
  }

}//go back to the first line in loop()





