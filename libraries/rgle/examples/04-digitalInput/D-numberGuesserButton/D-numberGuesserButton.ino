/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Number Guesser Game              | >_   |   
 *           With Button Reset         |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will genrerate a random number and prompt you to guess the number. Pressing
 *  the pushbutton will restart the program.
 *  Note: Pressing the button will not reset the program while it is waiting for name
 *  input.
 *  
 *  As in the previous example, the LED will light up when the correct number is guessed
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
 *  digitalWrite()
 *  digitalRead()
 *****************************************************************************************/

const int LED_PIN = 13;    //pin number for LED
const int BUTTON_PIN = 2;  //pin number for button
const int MAX_RANDOM_NUMBER = 1000;

int randomNumberToGuess;     //the random number that the user is trying to guess
int userGuess;               //the last guess the user entered
int gamesWon = 0;            //the number of times you have won the game

String nameString;  //holds the name of the user as a String (a series of characters)
bool startFlag = false;  //a 'flag' to check if the user has started the game  set to false to assume they have not since the Geekduino has just started up. 


//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(LED_PIN, OUTPUT);   //set LED as an output
  pinMode(BUTTON_PIN, INPUT); //set button as an input
  
  digitalWrite(LED_PIN, LOW); //set the LED low / off

  randomSeed(555);       //seed the random number generator based on a pre-defined number. 
    
  Serial.begin(9600);    //start the Serial port at a baud rate of 9600 bits per second (bps)
  

} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{

   /*************************************************************************
    * check to see if the game has not started yet / has been reset. 
    *************************************************************************/
   if(startFlag == false)
   {  
    digitalWrite(LED_PIN, LOW); //write the LED low, this will set the LED off if the program is started / restarted. Do this before anything else so that the LED turns off right away
    
    //print ASCII art text
    Serial.println("   ");
    Serial.println("   "); 
    Serial.println("   ");
    Serial.println("    /$$   /$$                         /$$                                  /$$$$$$                                                        "    );
    Serial.println("  | $$$ | $$                        | $$                                 /$$__  $$                                                        "   );
    Serial.println("  | $$$$| $$ /$$   /$$ /$$$$$$/$$$$ | $$$$$$$   /$$$$$$   /$$$$$$       | $$  \\__/ /$$   /$$  /$$$$$$   /$$$$$$$ /$$$$$$$  /$$$$$$   /$$$$$$" );
    Serial.println("  | $$ $$ $$| $$  | $$| $$_  $$_  $$| $$__  $$ /$$__  $$ /$$__  $$      | $$ /$$$$| $$  | $$ /$$__  $$ /$$_____//$$_____/ /$$__  $$ /$$__  $$");
    Serial.println("  | $$  $$$$| $$  | $$| $$ \\ $$ \\ $$| $$  \\ $$| $$$$$$$$| $$  \\__/      | $$|_  $$| $$  | $$| $$$$$$$$|  $$$$$$|  $$$$$$ | $$$$$$$$| $$  \\__/");
    Serial.println("  | $$\\  $$$| $$  | $$| $$ | $$ | $$| $$  | $$| $$_____/| $$            | $$  \\ $$| $$  | $$| $$_____/ \\____  $$\\____  $$| $$_____/| $$      ");
    Serial.println("  | $$ \\  $$|  $$$$$$/| $$ | $$ | $$| $$$$$$$/|  $$$$$$$| $$            |  $$$$$$/|  $$$$$$/|  $$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$$$| $$      ");
    Serial.println("  |__/  \\__/ \\______/ |__/ |__/ |__/|_______/  \\_______/|__/             \\______/  \\______/  \\_______/|_______/|_______/  \\_______/|__/      ");
    
    //generate the random number              
    randomNumberToGuess = random(MAX_RANDOM_NUMBER + 1);  //generate a random number
   
    //uncomment the next 2 lines if you want to see the random number for debugging
    //Serial.print("Random: "); 
    //Serial.println(randomNumberToGuess);   

    //print instructions
    Serial.print("Hello ! Please enter a number between 0 and "); 
    Serial.println(MAX_RANDOM_NUMBER); 
        
    startFlag = true;   //the game has started, so set the startFlag to true

  }//end if


   /*************************************************************************
   * check if the button has been pressed so that we can restart the program
   * digitalRead() returns HIGH if the button is pressed and LOW if it is not
   *************************************************************************/
  if(digitalRead(BUTTON_PIN) == HIGH)
  {
    startFlag = false;
  }

   /*************************************************************************
   * check is there are any characters incoming on the serial buffer.
   * Serial.available() returns the number of characters that have been input
   * so check if there are more than 0 characters
   *************************************************************************/
  if(Serial.available() > 0)
  {
    userGuess = Serial.parseInt(); //read one character from the serial buffer and remove that character from the buffer

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
    
    //if not, check if the number the user guessed is equal to the number to guess - if it is, then tell the user by printing a message and making changes that represent the game being won.
    else if(userGuess == randomNumberToGuess)
    {
      gamesWon = gamesWon + 1; //the game has been won, so increase the count.
      Serial.println("You guessed correctly!");//print static text
      
      Serial.print("You have won the game ");//print static text
      Serial.print(gamesWon);//print the value of the variable
      Serial.println(" time!");//print static text
      
      Serial.println("Press your pushbutton to restart the game.");  //print static text

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
    }//end else if
  }//end Serial.avaialble() if
  
}//go back to the first line in loop()





