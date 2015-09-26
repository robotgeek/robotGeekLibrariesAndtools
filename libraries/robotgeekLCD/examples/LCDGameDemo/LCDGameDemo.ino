/***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | | 'Collect the Hearts' Game     | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  The following sketch will use the RobotGeekLCD , a joystick, a knob, and a
 *   button to create a simple  video game
 *
 *  Products
 *    http://www.robotgeek.com/robotGeek-pushbutton
 *    http://www.robotgeek.com/robotgeek-lcd-wmount
 *    http://www.robotgeek.com/robotGeek-pushbutton
 *    http://www.robotgeek.com/robotgeek-rotation-knob
 *    http://www.robotgeek.com/robotgeek-joystick
 *  
 *  Wiring
 *    RobotGeek Sensor Shield With Geekduino
 *      The RobotGeek I2C LCD will plug directly into the 4-pin I2C port on
 *      the sensor shield using a 4-pin sensor cable. Normally the sensor cable
 *      will be plugged in with the following orientation:
 *        SCL    - Yellow
 *        SDA    - White
 *        5v/VCC - Red
 *        G/GND  - Black
 *  
 *   Digital Input  2 - Pushbutton       
 *   Analog Input 0 - Rotational Knob
 *   Analog Input 1 - Joystick Horizontal
 *   Analog Input 2 - Joystick Vertical
 *
 *
 *  Control Behavior:  
 *    The LCD will display title text, then randomly generate 'heart' icons
 *    across the LCD. In the upper right corner there will be a small stick 
 *    figure - your 'hero'. By moving the joustick up/down/left/right the user
 *    can control the 'hero' to collect the hearts. Once all the hearts are
 *    collected, a 'you win!' label appears.
 *    Clicking the pushbutton will reset the game and regenerate a new field
 *    of hearts. The hearts are randomly selected. The random seed is generated
 *    from the Knob.
 * 
 *
 *  References
 *      RobotGeek LCD Documentation http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
 *      RobotGeek Libraries and Tools (Included LCD Library) https://github.com/trossenrobotics/robotGeekLibrariesAndtools/archive/master.zip
 *      Custom Character guide http://learn.trossenrobotics.com/28-robotgeek-getting-started-guides/61-robotgeek-i2c-lcd-library#customChar 
 *  
 ***********************************************************************************/

#include <Wire.h>          //include the I2C Wire library - needed for communication with the I2C chip attached to the LCD manual 
#include <RobotGeekLCD.h>  // include the RobotGeekLCD library

//define analog input pins
#define KNOB_PIN 0
#define JOYSTICK_PIN_VERTICAL 1
#define JOYSTICK_PIN_HORIZONTAL 2

//define digital input pin
#define BUTTON_PIN 2

//low and high values for the deadband around the center of the joystick
#define DEADBANDLOW 482
#define DEADBANDHIGH 542



RobotGeekLCD lcd;   // create a robotgeekLCD object named 'lcd'


boolean field[2][16];   //2x16 array to keep track of where hearts are being displayed on the screen. 0 means no heart and 1 means a heart exists

int knobValue;              //holds the current value of the knob
int joystickHorizontalValue;//holds the current value of the horizontal joystick
int joystickVerticalValue;  //holds the current value of the vertical joystick

int heroRowPosition = 0;     //the row that the hero character is currently occupying       
int heroColumnPosition = 0;  //the column that the hero charcater is currenty occupying

//a byte array representing a stick figure with arms down
byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

//a byte array representing a stick figure with arms up
byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};


//a byte array representing a heart
byte heartFull[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};


int heroSprite = 1;  //the LCD character that represents the hero character - this will be defined with lcd.createChar. This defaults to '1', the stick figure with hands up
int reset = 0;       //a 'flag' to indicate that the game has been reset


void setup() 
{
  lcd.init();  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work


  // write a charcter to the 0 position on the HD44780 chip based on the byte array armsUp
  lcd.createChar(0, armsUp);  
  // write a charcter to the 1 position on the HD44780 chip based on the byte array armsDown
  lcd.createChar(1, armsDown);    
  // write a charcter to the 2 position on the HD44780 chip based on the byte array heartFull
  lcd.createChar(2, heartFull); 

  lcd.setCursor(0, 0);        // move the cursor to Column 0 in row 1 - i.e. the first character in the first row
  lcd.print("Collect the ");  // Print a message to the LCD.
  lcd.setCursor(0, 1);        // move the cursor to Column 0 in row 1 - i.e. the first character in the second row
  lcd.print("Hearts! ");       // Print a message to the LCD.
  lcd.write(2);               // print a 'heart' to the LCD
  delay(2000);                  //wait for 2000ms, 2 seconds
  lcd.clear();                  //clear the LCD to get ready to display the input data
  
  //digital input does not need to be intialized as it is on an interrupt pin and being used as an interupt
  //analog input do not need to be initialized
  
  randomSeed(analogRead(0));  //'seed'/setup the random function based on the value from the knob on pin 0 - this means the sequence should be the same every time you reboot the geekduino, for each setting of the knob. Disconnect the knob for a more 'random' value
  
  generateHeartField(); //this function will generate the heart field randomly, write it to the LCD and save it to field[][]. 
  resetHero();// reset the hero sprite to the correct position
    
  attachInterrupt(0, resetHearts, RISING ); //attach interupt 0(Pin 2 on the Geekduino) to function resetHearts() whenever the input is RISING (LOW to HIGH when the button is pressed)      
}

void loop() 
{
  //check if the game needs to be reset
  if(reset == 1)
  {
    generateHeartField(); //this function will generate the heart field randomly, write it to the LCD and save it to field[][]. 
    resetHero();// reset the hero sprite to the correct position   
    reset = 0; //set reset flag to '0' to show the program has completed the reset
  }
  
  int clearFlag = 0; //'flag' used to determine if the field[][] is cleared of hearts or not. 0 = not cleared 1 = cleared
  
  
  knobValue = analogRead(KNOB_PIN);
  delay(5); //short delay to allow the Analog to Digital Converter switch
  joystickHorizontalValue = analogRead(JOYSTICK_PIN_HORIZONTAL);
  delay(5); //short delay to allow the Analog to Digital Converter switch
  joystickVerticalValue = analogRead(JOYSTICK_PIN_VERTICAL);
  delay(5); //short delay to allow the Analog to Digital Converter switch
  
  //check if the horizontal joystick is above the high deadband
  //which signals the processer to move the charcter left
  if(joystickHorizontalValue > DEADBANDHIGH)
  {
    //check that the character is to the right of the first column (so that it does not go off-screen)
    if(heroColumnPosition - 1 >= 0)
     {
       heroSprite = (heroSprite +1)%2;                      //add one then use %2 on the heroSprite - this will alternate the heroSprite value between 0 and 1. This animates the hero between armsup/armsdown
       lcd.setCursor(heroColumnPosition, heroRowPosition);  //set the cursor to the hero's position
       lcd.print(" ");                                      //write a ' '(space) to the current positon since the here is moving out of that space
       heroColumnPosition = heroColumnPosition - 1;          //decrement the column position of the here by 1 - this 'moves' the hero left
       lcd.setCursor(heroColumnPosition, heroRowPosition);  //set the cursor to the new psotion for the hero
       lcd.write(heroSprite);                               //print the hero's sprite to the new position
     }
  }
  
  //check if the horizontal joystick is below the low deadband
  //which signals the processer to move the charcter right
  if(joystickHorizontalValue < DEADBANDLOW)
  {
    //check that the character is to the left of the last column (so that it does not go off-screen)
     if(heroColumnPosition + 1 <  16)
     {
   
       heroSprite = (heroSprite +1)%2;                      //add one then use %2 on the heroSprite - this will alternate the heroSprite value between 0 and 1. This animates the hero between armsup/armsdown
       lcd.setCursor(heroColumnPosition, heroRowPosition);
       lcd.print(" ");                                      //write a ' '(space) to the current positon since the here is moving out of that space     
       heroColumnPosition = heroColumnPosition + 1;         //incremebt the column position of the here by 1 - this 'moves' the hero right
       lcd.setCursor(heroColumnPosition, heroRowPosition);  //set the cursor to the new psotion for the hero
       lcd.write(heroSprite);                               //print the hero's sprite to the new position
     }
  }
  
  
    
  //check if the vertical joystick is below the low deadband
  //which signals the processer to move the charcter up
  if(joystickVerticalValue < DEADBANDLOW)
  
    //check that the character is below the first row (so that it does not go off-screen)
     if(heroRowPosition - 1 >= 0)
     {
       heroSprite = (heroSprite +1)%2;                      //add one then use %2 on the heroSprite - this will alternate the heroSprite value between 0 and 1. This animates the hero between armsup/armsdown
       lcd.setCursor(heroColumnPosition, heroRowPosition);
       lcd.print(" ");                                      //write a ' '(space) to the current positon since the here is moving out of that space      
       heroRowPosition = heroRowPosition - 1;            //decrement the row position of the here by 1 - this 'moves' the hero up
       lcd.setCursor(heroColumnPosition, heroRowPosition);  //set the cursor to the new psotion for the hero
       lcd.write(heroSprite);                               //print the hero's sprite to the new position
     }
  
  
  //check if the vertical joystick is above the high deadband
  //which signals the processer to move the charcter down
  if(joystickVerticalValue > DEADBANDHIGH)
  {
    //check that the character is above the last row (so that it does not go off-screen)
     if(heroRowPosition + 1 <  2)
     {
       
       heroSprite = (heroSprite +1)%2;                      //add one then use %2 on the heroSprite - this will alternate the heroSprite value between 0 and 1. This animates the hero between armsup/armsdown
       lcd.setCursor(heroColumnPosition, heroRowPosition);
       lcd.print(" ");                                      //write a ' '(space) to the current positon since the here is moving out of that space       
       heroRowPosition = heroRowPosition + 1;            //increment the row position of the here by 1 - this 'moves' the hero down
       lcd.setCursor(heroColumnPosition, heroRowPosition);  //set the cursor to the new psotion for the hero
       lcd.write(heroSprite);                               //print the hero's sprite to the new position
     }
  }
    
  field[heroRowPosition][heroColumnPosition] = 0; //set the value in field[][] array to '0' wherer the hero sprite currenty is occupying
  
  
  clearFlag = 1;  //set the clearFlag to '1' - this makes the assumption that the field is clear -this will be set to '0' if the loop finds any 'hearts' in the array
  
  //loop through the first dimension of the array
  for(int i=0;i<2;i++)
  {
     //loop through the second dimension of the array 
     for(int j = 0;j<16;j++)
     {
       //if the current element of the array is '1' then there is a heart on the screen
       if(field[i][j] == 1)
       {
         clearFlag = 0; //because at least one heart is still on the screen, set the clearFlag to '0'
       }
    } 
  }
  
  //check if the clearFlag is set to '1'
  if(clearFlag == 1)
  {
    //The game is over
    lcd.setCursor(0,0);    //set the cursor to the uper right corner
    lcd.print("You Win!"); //Display text to LCD
    heroSprite =2;         //Change the hero sprite to 2, a heart
   
    lcd.setCursor(heroColumnPosition, heroRowPosition);  //move cursor to the hero position
    lcd.write(heroSprite);                               //redrwar the hero sprite

  }
  
  delay(100); //a short delay slow the speed of the game - lower this value to speed up the game
}

//this function is called when the button on pin 2 is pressed because of the interrupt
//this function will 'interupt' the program flow and execute when the button is pressed
//this function is considered an interupt service routine (ISR)
void resetHearts()
{
  reset = 1;  //set the reset flag to 1, so that the main loop can reset the heart field
  //I2C communications do not work in the ISR, so this function cannot send commands to the LCD
 }
 

//this function will generate the heart field randomly, write it to the LCD and save it to field[][]. 
void generateHeartField()
{
  //loop through the first dimension of the array
  for(int i=0;i<2;i++)
  {
     //loop through the second dimension of the array 
     for(int j = 0;j<16;j++)
    {
        lcd.setCursor(j, i);  //move the cursor to the current position that the loop is inspecting

        //generate a random number from 0-10 with random(10). If this value is greater than 5, then write a heart to the LCD
        //and to the corresponding array element.
        //increase '5' to increase the heart density and lower it to lower the heart density in the field 
       if(random(10) < 5)
       {
        lcd.write(2);         //write a heart to the LCD
        field[i][j] = 1;      //write a '1' to the array to signify a heart existing
       }
       else
       {
        lcd.print(" ");       //write a blank ' '(space) to the lcd
        field[i][j] = 0;      //write a '0' to the array to signify no heart existing

       }
    } 
  }    
}

// reset the hero sprite to the correct position
void resetHero()
{
  lcd.setCursor(heroColumnPosition, heroRowPosition); //set the cursor to the hero's starting position (by defualt(0,0) upper left corner
  heroSprite = 1;                                     //reset the hero sprite to the default character
  lcd.write(heroSprite);                              //print the hero character to the LCD    
}




