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
 *  randomSeed()
 *  digitalWrite()
 *****************************************************************************************/

const int LED_PIN = 13; //pin for the LED driver

char incomingData;  //create an empty chracter variable to hold the incoming data, one character at a time
int randomNumber;      //the random number that the user is trying to guess
int guess;             //the last guess the user entered

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT);   //set LED as an output
  digitalWrite(LED_PIN, LOW); //turn the LED off

  randomSeed(analogRead(7));        //seed the random number generator based on a 'random' reading from an unconnected analog input
  randomNumber = random(1001);   //generate a random number

  Serial.begin(9600);                                               //start the Serial port at a baud rate of 9600 bits per second (bps)
  
  readUsersName(); // read the users name - make sure to call this after the Serial port has been started

  //uncomment the next 2 lines if you want to see the random number for debugging
  //Serial.print("Random: "); 
  //Serial.println(randomNumber); 

  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //check is there are any characters incoming on the serial buffer.
  if(Serial.available() > 0)
  {
    guess = Serial.parseInt(); //read one character from the serial buffer and remove that character from the buffer
    
     Serial.print("You Guessed: ");  //print static text
     Serial.println(guess); //print the data that was recieved

    if(guess > randomNumber)
    {
      Serial.println("You Guess is too high");  //print static text
    }
    else if(guess < randomNumber)
    {
      Serial.println("You Guess is too low");  //print static text
    }
    else if(guess == randomNumber)
    {
      Serial.println("You guessed correctly!");  //print static text

      //flash the LED on/off 
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


void readUsersName()
{
  String nameString;  //holds the name of the user as a String (an series of characters)
  bool nameFlag = false;  //a flag to check if the user has started the game / put in their name yet, set to false to assume they have not. We will also use this to reset the program if the button is pressed

  Serial.println("Please Enter Your Name"); //print a header one time
  
   //loop while the nameFlag is still false (i.e. no name has been entered)
  while(nameFlag == false)
  {
    //see if data is available on the serial port
    if(Serial.available() == true)
    {
      nameString = Serial.readString(); //read the data as a string

      nameFlag = true; //a string has been sucessfully read, so change the flag so that we can leave the while loop

    }
  }
  //print prompts  
  Serial.print("Hello "); 
  Serial.print(nameString); 
  Serial.println("! Please enter a number between 0 and 1000. "); 
  
}




