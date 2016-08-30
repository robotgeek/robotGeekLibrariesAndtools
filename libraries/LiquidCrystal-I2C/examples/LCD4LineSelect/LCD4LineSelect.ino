/* 4 Line LCD - List Selection Example
 *  
 *  Code Behavior: As you press up and down buttons, LCD Scrolls through a predefined list.
 * 
 * 
 * I2C - RobotGeek 2 line LCD
 * Digital Pin 16 - Up Button
 * Digital Pin 17 - Down Button
 * Digital Pin 20 - Enter Button
 * Digital Pin 21 - Back Button
 */


// Libraries
#include <Bounce2.h>              //Load the Debouncing Library
#include <Wire.h>                 //Load for I2C
#include <LiquidCrystal_I2C.h>    //Load the LiquidCrystal I2C Library for the 4 Line LCD Display

// Buttons
const int BUTTON_PIN[4] = {16, 17, 20, 21};
int value[4] = {16, 17, 20, 21};



// LCD Screen
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to blink (milliseconds)

// Prompts
String promptLine[4] = {
                   "Oh, hi there!      ", 
                   "Select Mixture:    ",
                   "OK!                ",
                   "BACK               "
                   };

// Selections
String selectionLine[14] = {
                   "                   ",  //buffer line
                   "1. Red             ", 
                   "2. Green           ",
                   "3. Blue            ",
                   "4. Yellow          ",
                   "5. Red & Green     ",
                   "6. Red & Blue      ",
                   "7. Red & Yellow    ", 
                   "8. Green & Blue    ",
                   "9. Green & Yellow  ",
                   "10. Blue & Yellow  ",
                   "                   ",  //buffer line
                   "                   ",  //buffer line
                   "End of List        "   //buffer line
                   };



// Create objects
Bounce debounce[4] = Bounce();       //Debouncing Library
LiquidCrystal_I2C lcd(0x27, 20, 4);  //I2C 4 Line LCD Screen

int delayval = 500; // delay for half a second
int promptSelect = 1;
int drinkSelectCounter = 1;
int PUMP_TIME = 2500; //Time for pumping stations to turn on in milliseconds

//setup() runs once
void setup()
{
  
  // Setup the button with an internal pull-up :
  for (int i = 0; i < 4; i = i + 1) 
  {
    pinMode(BUTTON_PIN[i],INPUT_PULLUP);
    debounce[i].attach(BUTTON_PIN[i]);
    debounce[i].interval(5);
  }
  
  //pixels.begin(); // This initializes the NeoPixel library.
  
  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.begin();
  lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Mix it up!");
  delay(500);
}

//loop() runs indefinitely
void loop()
{
  // Update the Bounce instance:
  for (int i = 0; i < 4; i = i + 1) 
  {
    debounce[i].update();
    value[i] = debounce[i].read();
  }


  // LCD
  unsigned long currentMillis = millis(); // Update currentMillis
  if(currentMillis - previousMillis > interval) 
    {
      // save the last time you refreshed the LCD 
      previousMillis = currentMillis;   
      lcd.setCursor(0, 0);
      lcd.print(promptLine[promptSelect]);
      lcd.setCursor(0, 1);
      lcd.print('>');
      lcd.setCursor(1, 1);
      lcd.print(selectionLine[(drinkSelectCounter)]);
      lcd.setCursor(1, 2);
      lcd.print(selectionLine[(drinkSelectCounter + 1)]);
      lcd.setCursor(1, 3);
      lcd.print(selectionLine[(drinkSelectCounter + 2)]);
    }

  drinkSelectCounter = constrain(drinkSelectCounter, 1, 10); //constrain the possible selection numbers for the drink counter
  
  //Buttons
  if ( debounce[0].fell() )
  {
    drinkSelectCounter = (drinkSelectCounter - 1);
  } 

  if ( debounce[1].fell() )
  {
    drinkSelectCounter = (drinkSelectCounter + 1);
    
  } 

  if ( debounce[2].fell() )
  {
    //Select function goes here
  }
  
  if ( debounce[3].fell() )
  {
    //Back function goes here
  }

}
