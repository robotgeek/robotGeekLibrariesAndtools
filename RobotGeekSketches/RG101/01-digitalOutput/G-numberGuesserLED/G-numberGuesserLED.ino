/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Number Guesser Game              | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will genrerate a random number and prompt you to guess the number.
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
 *  Serial.read()
 *  Serial.parseInt()
 *  Serial.readString()
 *  rand()
 *****************************************************************************************/

const int LED_PIN = 13;

char incomingData;  //create an empty chracter variable to hold the incoming data
String nameString;

bool nameFlag = false;  //a flag to check if the user has put in their name yet, set to false to assume they have not
int randomNumber;
int guess;
//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  randomSeed(analogRead(0));        //seed the random number generator based on a 'random' reading from an unconnected analog input
  randomNumber = random(0, 1001);  //generate a random number

  Serial.begin(9600);                                               //start the Serial port at a baud rate of 9600 bits per second (bps)
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





