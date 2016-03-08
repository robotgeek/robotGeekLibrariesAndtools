/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Adventure Text Game              | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  This code will create a short 'Choose Your Own Adventure' style game.
 *
 *  All of the strings that we send to print/println will be wrapped in the
 *  F() macro, which will store the string in Flash memory instead of RAM
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
 *****************************************************************************************/
#include <avr/pgmspace.h> //included PROGMEM library so we can store string in flash memory



String nameString;

bool nameFlag = false;  //a flag to check if the user has put in their name yet, set to false to assume they have not
int level;              //keep track of the game level
int choice;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  Serial.begin(9600);                                               //start the Serial port at a baud rate of 9600 bits per second (bps)
  Serial.println(F("Please Enter Your Name")); //print a header one time
  
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
  

  Serial.println(F("/$$$$$$$$                    /$$            /$$$$$$        /$$                                 /$$"));                                  
  Serial.println(F("|__  $$__/                   | $$           /$$__  $$      | $$                                | $$"));                                  
  Serial.println(F("   | $$  /$$$$$$  /$$   /$$ /$$$$$$        | $$  \\ $$  /$$$$$$$ /$$    /$$ /$$$$$$  /$$$$$$$  /$$$$$$   /$$   /$$  /$$$$$$   /$$$$$$ "));
  Serial.println(F("   | $$ /$$__  $$|  $$ /$$/|_  $$_/        | $$$$$$$$ /$$__  $$|  $$  /$$//$$__  $$| $$__  $$|_  $$_/  | $$  | $$ /$$__  $$ /$$__  $$"));
  Serial.println(F("   | $$| $$$$$$$$ \\  $$$$/   | $$          | $$__  $$| $$  | $$ \\  $$/$$/| $$$$$$$$| $$  \\ $$  | $$    | $$  | $$| $$  \\__/| $$$$$$$$"));
  Serial.println(F("   | $$| $$_____/  >$$  $$   | $$ /$$      | $$  | $$| $$  | $$  \\  $$$/ | $$_____/| $$  | $$  | $$ /$$| $$  | $$| $$      | $$_____/"));
  Serial.println(F("   | $$|  $$$$$$$ /$$/\\  $$  |  $$$$/      | $$  | $$|  $$$$$$$   \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$/| $$      |  $$$$$$$"));
  Serial.println(F("   |__/ \\_______/|__/  \\__/   \\___/        |__/  |__/ \\_______/    \\_/    \\_______/|__/  |__/   \\___/   \\______/ |__/       \\_______/"));



  Serial.println(F(""));
  Serial.println(F(""));
  Serial.print(F("Hello ")); 
  Serial.print(nameString); 
  Serial.print(F("! "));


  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{


  Serial.println(F(""));

  Serial.println(F("___________________________________  "));
  Serial.println(F("| _____ |   | ___ | ___ ___ | |   | |"));
  Serial.println(F("| |   | |_| |__ | |_| __|____ | | | |"));
  Serial.println(F("| | | |_________|__ |______ |___|_| |"));
  Serial.println(F("| |_|   | _______ |______ |   | ____|"));
  Serial.println(F("| ___ | |____ | |______ | |_| |____ |"));
  Serial.println(F("|___|_|____ | |   ___ | |________ | |"));
  Serial.println(F("|   ________| | |__ | |______ | | | |"));
  Serial.println(F("| | | ________| | __|____ | | | __| |"));
  Serial.println(F("|_| |__ |   | __|__ | ____| | |_| __|"));
  Serial.println(F("|   ____| | |____ | |__ |   |__ |__ |"));
  Serial.println(F("| |_______|_______|___|___|___|_____|"));


  Serial.println(F("You find yourself in a giant labyrinth.  There are two paths in front of you. ")); 
  Serial.println(F("Enter 1 to go left"));
  Serial.println(F("Enter 2 to go right")); 

  choice = readChoice();


  if(choice == 1)
  {

  Serial.println(F("You start along the left path. After a few minutes you come across a small table with a cake on it.  ")); 
  Serial.println(F(""));           
  Serial.println(F("                             (             )"));
  Serial.println(F("                     )      (*)           (*)      ("));
  Serial.println(F("                    (*)      |             |      (*)"));
  Serial.println(F("                     |      |~|           |~|      |    "));      
  Serial.println(F("                    |~|     | |           | |     |~|"));
  Serial.println(F("                    | |     | |           | |     | |"));
  Serial.println(F("                   ,| |a@@@@| |@@@@@@@@@@@| |@@@@a| |."));
  Serial.println(F("              .,a@@@| |@@@@@| |@@@@@@@@@@@| |@@@@@| |@@@@a,."));
  Serial.println(F("            ,a@@@@@@| |@@@@@@@@@@@@.@@@@@@@@@@@@@@| |@@@@@@@a,"));
  Serial.println(F("           a@@@@@@@@@@@@@@@@@@@@@' . `@@@@@@@@@@@@@@@@@@@@@@@@a"));
  Serial.println(F("           ;`@@@@@@@@@@@@@@@@@@'   .   `@@@@@@@@@@@@@@@@@@@@@';"));
  Serial.println(F("           ;@@@`@@@@@@@@@@@@@'     .     `@@@@@@@@@@@@@@@@'@@@;"));
  Serial.println(F("           ;@@@;,.aaaaaaaaaa       .       aaaaa,,aaaaaaa,;@@@;"));
  Serial.println(F("           ;;@;;;;@@@@@@@@;@      @.@      ;@@@;;;@@@@@@;;;;@@;"));
  Serial.println(F("           ;;;;;;;@@@@;@@;;@    @@ . @@    ;;@;;;;@@;@@@;;;;;;;"));
  Serial.println(F("           ;;;;;;;;@@;;;;;;;  @@   .   @@  ;;;;;;;;;;;@@;;;;@;;"));
  Serial.println(F("           ;;;;;;;;;;;;;;;;;@@     .     @@;;;;;;;;;;;;;;;;@@@;"));
  Serial.println(F("       ,%%%;;;;;;;;@;;;;;;;;       .       ;;;;;;;;;;;;;;;;@@;;%%%,"));
  Serial.println(F("    .%%%%%%;;;;;;;@@;;;;;;;;     ,%%%,     ;;;;;;;;;;;;;;;;;;;;%%%%%%,"));
  Serial.println(F("   .%%%%%%%;;;;;;;@@;;;;;;;;   ,%%%%%%%,   ;;;;;;;;;;;;;;;;;;;;%%%%%%%,"));
  Serial.println(F("   %%%%%%%%`;;;;;;;;;;;;;;;;  %%%%%%%%%%%  ;;;;;;;;;;;;;;;;;;;'%%%%%%%%"));
  Serial.println(F("   %%%%%%%%%%%%`;;;;;;;;;;;;,%%%%%%%%%%%%%,;;;;;;;;;;;;;;;'%%%%%%%%%%%%"));
  Serial.println(F("   `%%%%%%%%%%%%%%%%%,,,,,,,%%%%%%%%%%%%%%%,,,,,,,%%%%%%%%%%%%%%%%%%%%'"));
  Serial.println(F("     `%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'"));
  Serial.println(F("         `%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'"));

                


    Serial.println(F("Enter 1 to eat the cake"));
    Serial.println(F("Enter 2 to keep going")); 

    choice = readChoice();

    if(choice == 1)
    {

      Serial.println(F(""));
      Serial.println(F("The cake is delicious and moist, but on your second slice you bite down into something hard! "));
      Serial.println(F("Someone put a key in the cake! You look around and see 2 doors you didn't notice before. Each door has an old lock on it.  ")); 


      Serial.println(F("Enter 1 to use the key on the metal door"));
      Serial.println(F("Enter 2 to use the key on the wood door")); 

      choice = readChoice();

      if(choice == 1)
      {

        Serial.println(F(""));
        Serial.println(F("You open the metal door, seeing only more of the labyrinth. As you go through the door it shuts behind you. That's when you realized you're back at the beginning of the labyrinth!   ")); 
        //there are no choices here, so the code will go back to the beginning of the loop()



      }
      else if (choice == 2)
      {
        randomSeed(analogRead(0));
        int randomNumber = random(1,3); //generate a random number between 1 and 2

        Serial.println(randomNumber);
        
        Serial.println(F(""));
        Serial.println(F("You are able to open the wood door. As you pass through the threshold the door dissapears behind you."));

        Serial.println(F("         (                       ("));
        Serial.println(F("        )  )                    )  )"));
        Serial.println(F("      _(______                _(______"));
        Serial.println(F("     (________)              (________)"));
        Serial.println(F("      )      (                )      ("));
        Serial.println(F("     /        \\              /        \\"));
        Serial.println(F(" ___|          |___      ___|          |___"));
        Serial.println(F("()__\\___ _   __/__()    ()__\\___ _   __/__()"));
        Serial.println(F("    .`/``||``\\`.           .`/``||``\\`."));
        Serial.println(F("  ()/   ()   \\()         ()/   ()   \\()"));



        Serial.println(F("You see two cauldrons, each with a liquid in it. There's a spoon that you can use to scoop out some liquid. ")); 
        Serial.println(F("Enter 1 to drink the red potion from the left cauldron"));
        Serial.println(F("Enter 2 to drink the blue potion from the right cauldron")); 

        choice = readChoice();

        //this outcome is based on randomNumber - if the choice is equal to the random number, then they win. If not, they lose
        if(choice == randomNumber)
        {   
          Serial.println(F(""));   
          Serial.println(F("As you sip on the liquid you start to feel something happening to your back. You've sprouted wings!"));
          Serial.println(F("You try flapping them and find it very easy to fly! You make it over the labyrinth walls - congratualtions, you've escaped the labyrinth!")); 
          Serial.println(F(" /$$     /$$                                      /$$           /$$")); 
          Serial.println(F("|  $$   /$$/                                     |__/          | $$")); 
          Serial.println(F(" \\  $$ /$$//$$$$$$  /$$   /$$       /$$  /$$  /$$ /$$ /$$$$$$$ | $$")); 
          Serial.println(F("  \\  $$$$//$$__  $$| $$  | $$      | $$ | $$ | $$| $$| $$__  $$| $$")); 
          Serial.println(F("   \\  $$/| $$  \\ $$| $$  | $$      | $$ | $$ | $$| $$| $$  \\ $$|__/")); 
          Serial.println(F("    | $$ | $$  | $$| $$  | $$      | $$ | $$ | $$| $$| $$  | $$    ")); 
          Serial.println(F("    | $$ |  $$$$$$/|  $$$$$$/      |  $$$$$/$$$$/| $$| $$  | $$ /$$")); 
          Serial.println(F("    |__/  \\______/  \\______/        \\_____/\\___/ |__/|__/  |__/|__/")); 
                                                                     
                                                                     
                                                                     

          Serial.println(F("Enter 1 or 2 to start again"));
          choice = readChoice();
          //there are no choices here, so the code will go back to the beginning of the loop()

        }
        else
        {      
          Serial.println(F(""));
          Serial.println(F("As you sip on the liquid you start to feel sleepy."));
          Serial.println(F("You slump along the wall and thats when you notice that all around the room are other people just like you sleeping along the wall! You're cursed to sleep forever in the labyrinth!")); 
        Serial.println(F("/$$     /$$                        /$$                                     /$$"));
        Serial.println(F("|  $$   /$$/                       | $$                                    | $$"));
        Serial.println(F(" \\  $$ /$$//$$$$$$  /$$   /$$      | $$        /$$$$$$   /$$$$$$$  /$$$$$$ | $$"));
        Serial.println(F("  \\  $$$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$_____/ /$$__  $$| $$"));
        Serial.println(F("   \\  $$/| $$  \\ $$| $$  | $$      | $$      | $$  \\ $$|  $$$$$$ | $$$$$$$$|__/"));
        Serial.println(F("    | $$ | $$  | $$| $$  | $$      | $$      | $$  | $$ \\____  $$| $$_____/    "));
        Serial.println(F("    | $$ |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/ /$$$$$$$/|  $$$$$$$ /$$"));
        Serial.println(F("    |__/  \\______/  \\______/       |________/ \\______/ |_______/  \\_______/|__/"));
                                                                                       
          Serial.println(F("Enter 1 or 2 to start again"));
          choice = readChoice();
          //there are no choices here, so the code will go back to the beginning of the loop()

        }

      }


    }
    else if (choice == 2)
    {
      Serial.println(F(""));
      Serial.println(F("You think the cake is a trap, so you ignore it. You keep on walking, for what seems like hours. Eventually you try to go back towards the cake, but even after hours and hours of walking you never seem to find it. You're stuck in the labyrinth forvever!")); 
        Serial.println(F("/$$     /$$                        /$$                                     /$$"));
        Serial.println(F("|  $$   /$$/                       | $$                                    | $$"));
        Serial.println(F(" \\  $$ /$$//$$$$$$  /$$   /$$      | $$        /$$$$$$   /$$$$$$$  /$$$$$$ | $$"));
        Serial.println(F("  \\  $$$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$_____/ /$$__  $$| $$"));
        Serial.println(F("   \\  $$/| $$  \\ $$| $$  | $$      | $$      | $$  \\ $$|  $$$$$$ | $$$$$$$$|__/"));
        Serial.println(F("    | $$ | $$  | $$| $$  | $$      | $$      | $$  | $$ \\____  $$| $$_____/    "));
        Serial.println(F("    | $$ |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/ /$$$$$$$/|  $$$$$$$ /$$"));
        Serial.println(F("    |__/  \\______/  \\______/       |________/ \\______/ |_______/  \\_______/|__/"));
                                                                                       
      Serial.println(F("Enter 1 or 2 to start again"));
      choice = readChoice();
      //there are no choices here, so the code will go back to the beginning of the loop()

    }

  }
  else if(choice ==2)
  {
    Serial.println(F(""));
    Serial.println(F("You start along the right path. After a few minutes you come across a panel with 2 buttons on it.  ")); 
    Serial.println(F("Enter 1 press the red button"));
    Serial.println(F("Enter 2 to green button")); 

    choice = readChoice();

    if(choice == 1)
    {
      Serial.println(F(""));
      Serial.println(F("You Press the red button and the wall of the room opens up to show a huge computer screen."));
      Serial.println(F("On the screen you can see a huge meteor hurtling towards the labyrinth!" ));
      Serial.println(F("There's a switch next to the computer with 2 labels - to the left is labeled 'laser' to the right is labeled 'missle'   ")); 
      Serial.println(F("Enter 1 to flip the switch to the left"));
      Serial.println(F("Enter 2 to flip the switch to the right")); 

      choice = readChoice();

      if(choice == 1)
      {
        Serial.println(F(""));
        Serial.println(F("You flip the switch to 'laser'. You see on the screen as a laser shoots out of the labyrinth, but it has no effect on the meteor!" ));
        Serial.println(F("You try to flip the switch back to 'missle' but it's to late, the meteor hits the labyrinth! You feel the entire structure shake and the lights flicker. "));
        Serial.println(F("You seem to be alright, but your heart sinks when you look at the screen. The only way out of the labyrinth has been destroyed by the meteor! You're stuck in the labyrinth forever!   ")); 
        Serial.println(F("/$$     /$$                        /$$                                     /$$"));
        Serial.println(F("|  $$   /$$/                       | $$                                    | $$"));
        Serial.println(F(" \\  $$ /$$//$$$$$$  /$$   /$$      | $$        /$$$$$$   /$$$$$$$  /$$$$$$ | $$"));
        Serial.println(F("  \\  $$$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$_____/ /$$__  $$| $$"));
        Serial.println(F("   \\  $$/| $$  \\ $$| $$  | $$      | $$      | $$  \\ $$|  $$$$$$ | $$$$$$$$|__/"));
        Serial.println(F("    | $$ | $$  | $$| $$  | $$      | $$      | $$  | $$ \\____  $$| $$_____/    "));
        Serial.println(F("    | $$ |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/ /$$$$$$$/|  $$$$$$$ /$$"));
        Serial.println(F("    |__/  \\______/  \\______/       |________/ \\______/ |_______/  \\_______/|__/"));
                                                                                       
                                                                                 
                                                                                 

        Serial.println(F("Enter 1 or 2 to start again"));
        choice = readChoice();
       //there are no choices here, so the code will go back to the beginning of the loop()
      }
      else if (choice == 2)
      {
        Serial.println(F(""));
        Serial.println(F("You flip the switch to 'missle'. You see on the screen as a missle shoots out of the labyrinth." ));
        Serial.println(F("It flies toward the meteor and makes a direct impact! You can see on the screen that pieces of debris are  falling down onto the labyrinth." ));
        Serial.println(F("One of the pieces of meteor crashes through a wall near you. You can see a hole just big enough to for through. You've done it, you've escaped! "));  Serial.println(F(" /$$     /$$                                      /$$           /$$")); 
        Serial.println(F("|  $$   /$$/                                     |__/          | $$")); 
        Serial.println(F(" \\  $$ /$$//$$$$$$  /$$   /$$       /$$  /$$  /$$ /$$ /$$$$$$$ | $$")); 
        Serial.println(F("  \\  $$$$//$$__  $$| $$  | $$      | $$ | $$ | $$| $$| $$__  $$| $$")); 
        Serial.println(F("   \\  $$/| $$  \\ $$| $$  | $$      | $$ | $$ | $$| $$| $$  \\ $$|__/")); 
        Serial.println(F("    | $$ | $$  | $$| $$  | $$      | $$ | $$ | $$| $$| $$  | $$    ")); 
        Serial.println(F("    | $$ |  $$$$$$/|  $$$$$$/      |  $$$$$/$$$$/| $$| $$  | $$ /$$")); 
        Serial.println(F("    |__/  \\______/  \\______/        \\_____/\\___/ |__/|__/  |__/|__/")); 
        Serial.println(F("Enter 1 or 2 to start again"));
        choice = readChoice();
      }

    }
    else if (choice == 2)
    {
      Serial.println(F(""));
      Serial.println(F("You Press the green button and you are teleported back to the start of the labyrinth! ")); 
      //there are no choices here, so the code will go back to the beginning of the loop()
    }

  }








  
}//go back to the first line in loop()

 /**********************************************
 * readChoice()
 *  Parameters: none
 *  returns: integer, the user's choice (1 or 2)
 *
 *  This function waits for user input. It expects
 *  a single '1' or '2' ascii character. If the
 *  incoming character is not a '1' or a '2' then
 *  the function will request the user try again
 *  until valid data is entered.
 *
 **********************************************/

int readChoice()
{
  bool readFlag = false;  //used to check if we have valid data
  char choice;            //holds the choice calue in a character

  while (readFlag == false)
  {
    if(Serial.available() > 1)
    {
      Serial.println(F("You have entered too many characters. Please enter '1' or '2'"));
      //we need to discard the bad data, so use Serial.read() to read characters until Serial.available()  shows there's no data in the buffer
      while(Serial.available() > 0)
      {
        Serial.read(); 
      }

    }
    else if(Serial.available() == 1)
    {
      choice = Serial.read();
      //check if the choice matches a '1' character. Notice we're using '' around 1. This is because when the user sends '1' over the serial monitor, they are not sending the value 1, but the character '1'
      if(choice == '1')
      {
        return(1); //return the numeric value 1
      }
      //check if the choice matches a '2' character. Notice we're using '' around 2. This is because when the user sends '2' over the serial monitor, they are not sending the value 2, but the character '2'
      else if(choice == '2')
      {
        return(2); //return the numeric value 2
      }
      else
      {
        Serial.println(F("Character not recognized. Please enter '1' or '2'"));
      }
    }
  }
}


