/* 4 Line LCD - List Selection Example
 *  
 *  Code Behavior: As you press up and down buttons, LCD Scrolls through a predefined list.
 *  Selecting a menu item with the play button activates the pump and a set of valves, delivering
 *  liquid from one or multiple sources, then clearing the line with air.
 * 
 * DIO-2  - Pump Relay
 * DIO-4  - Air Line Solenoid Relay
 * DIO-6  - Neopixel Ring
 * DIO-7  - Left Solenoid Relay 1
 * DIO-8  - Left Solenoid Relay 2
 * DIO-9  - Right Solenoid Relay 1
 * DIO-10 - Right Solenoid Relay 2 
 * DIO-11 - Right Solenoid Relay 3
 * DIO-12 - Left Solenoid Relay 3
 * I2C    - RobotGeek 2 line LCD
 * DIO-14 (AIO-0) - Up Button
 * DIO-15 (AIO-1) - Down Button
 * DIO-16 (AIO-2) - Enter Button
 * DIO-17 (AIO-3) - Back Button
 * 
 * NOTES: You can power the pump and solenoids off of the same 12V10A Power Supply. Run the Geekduino
 * on a SEPARATE power supply (USB or 6V2A). Running the Geekduino on the same power supply as the
 * Pump and Relays will cause your board to reset.
 */


// Libraries
#include <Bounce2.h>              //Load the Debouncing Library
#include <Wire.h>                 //Load for I2C
#include <LiquidCrystal_I2C.h>    //Load the LiquidCrystal I2C Library for the 4 Line LCD Display
#include <Adafruit_NeoPixel.h>    //Load the Neopixel Library


// Buttons
const int BUTTON_PIN[4] = {14, 15, 16, 17};
int value[4] = {14, 15, 16, 17};

// Relays
const int PUMP_RELAY_PIN = 2;
const int CLEAN_RELAY_PIN = 4;
const int SELECTED_RELAY_PIN[6] = {7, 8, 12, 9, 10, 11};

//Neopixels
const int NEOPIXEL_PIN = 6;

// LCD Screen
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to blink (milliseconds)

// Prompts
String promptLine[4] = {
                   "Oh, hi there!      ", 
                   "Select Mixture:    ",
                   "OK!                ",
                   "CLEANING           "
                   };

// Selections
String selectionLine[14] = {
                   "                   ",  //buffer line
                   "1. Red             ", 
                   "2. Green           ",
                   "3. Blue            ",
                   "4. Yellow          ",
                   "5. White           ",
                   "6. Black           ",
                   "7. Red & Yellow    ", 
                   "8. Green & Blue    ",
                   "9. Black & White   ",
                   "10. Black & Yellow ",
                   "                   ",  //buffer line
                   "                   ",  //buffer line
                   "End of List        "   //buffer line
                   };



// Create objects
Bounce debounce[4] = Bounce();       //Debouncing Library
LiquidCrystal_I2C lcd(0x27, 20, 4);  //I2C 4 Line LCD Screen
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //Neopixel strip. (Number of LEDs, Pin, Pixels are wired for GRB bitstream and 800 KHz bitstream )

int delayval = 500;         // delay for half a second
int promptSelect = 1;       // Initialize prompt at 1
int drinkSelectCounter = 1; // Initialize Drink Selection at 1
int PUMP_TIME = 2500;       //Time for pumping station to run in milliseconds

//setup() runs once
void setup()
{
  // Setup the pump and air relay pins as Output :
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(CLEAN_RELAY_PIN, OUTPUT);
  // Setup the liquid relay pins as Output :
  for (int i = 0; i < 6; i = i + 1) 
  {
    pinMode(SELECTED_RELAY_PIN[i], OUTPUT);
  }
  
  // Setup the button with an internal pull-up :
  for (int i = 0; i < 4; i = i + 1) 
  {
    pinMode(BUTTON_PIN[i],INPUT_PULLUP);
    debounce[i].attach(BUTTON_PIN[i]);
    debounce[i].interval(5);
  }

  // Neopixel:
  strip.begin(); // This initializes the NeoPixel library.
  strip.show();  // Initialize all pixels to 'off'
  
  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.begin();
  lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Mix it up!");
  delay(delayval);
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
  
  colorWipe(strip.Color(0, 0, 0), 0); // Reset the Neopixel Strip

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
    switch (drinkSelectCounter)
    {
      case 1: // Red
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(255, 0, 0), 50); // Red
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[0], HIGH); // Open Solenoid valve 1
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[0], LOW); // Close Solenoid valve 1
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;

      case 2: // Green
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(0, 255, 0), 50); // Green
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[1], HIGH); // Open Solenoid valve 2
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[1], LOW); // Close Solenoid valve 2
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;

      case 3: // Blue
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[2], HIGH); // Open Solenoid valve 3
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[2], LOW); // Close Solenoid valve 3
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;

      case 4: // Yellow
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(255, 255, 0), 50); // Yellow
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[3], HIGH); // Open Solenoid valve 4
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[3], LOW); // Close Solenoid valve 4
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;

      case 5: // White
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(255, 255, 255), 50); // White
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[4], HIGH); // Open Solenoid valve 5
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[4], LOW); // Close Solenoid valve 5
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;

      case 6: // Black
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(5, 5, 5), 50); // Black
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[5], HIGH); // Open Solenoid valve 6
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[5], LOW); // Close Solenoid valve 6
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;     

      case 7: // Red and Yellow
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(255, 0, 0), 50); // Red
      colorWipe(strip.Color(255, 255, 0), 50); // Yellow
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[0], HIGH); // Open Solenoid valve 1
      digitalWrite(SELECTED_RELAY_PIN[3], HIGH); // Open Solenoid valve 4
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[0], LOW); // Open Solenoid valve 1
      digitalWrite(SELECTED_RELAY_PIN[3], LOW); // Open Solenoid valve 4
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;   
      
      case 8: // Green and Blue
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(0, 255, 0), 50); // Green
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[1], HIGH); // Open Solenoid valve 2
      digitalWrite(SELECTED_RELAY_PIN[2], HIGH); // Open Solenoid valve 3
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[1], LOW); // Open Solenoid valve 2
      digitalWrite(SELECTED_RELAY_PIN[2], LOW); // Open Solenoid valve 3
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;   
      
      case 9: // White and Black
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(255, 255, 255), 50); // White
      colorWipe(strip.Color(5, 5, 5), 50); // Black
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[4], HIGH); // Open Solenoid valve 5
      digitalWrite(SELECTED_RELAY_PIN[5], HIGH); // Open Solenoid valve 6
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[4], LOW); // Open Solenoid valve 5
      digitalWrite(SELECTED_RELAY_PIN[5], LOW); // Open Solenoid valve 6
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;  

      case 10: // Black and Yellow
      lcd.setCursor(0, 0);
      lcd.print(promptLine[2]);
      colorWipe(strip.Color(5, 5, 5), 50); // Black
      colorWipe(strip.Color(255, 255, 0), 50); // Yellow
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
      digitalWrite(SELECTED_RELAY_PIN[3], HIGH); // Open Solenoid valve 4
      digitalWrite(SELECTED_RELAY_PIN[5], HIGH); // Open Solenoid valve 6
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(SELECTED_RELAY_PIN[3], LOW); // Open Solenoid valve 4
      digitalWrite(SELECTED_RELAY_PIN[5], LOW); // Open Solenoid valve 6
      digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
      delay(PUMP_TIME); // Run for the set amount of time
      digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
      digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
      break;  
      
    } 
  }
  
  if ( debounce[3].fell() )
  {
    lcd.setCursor(0, 0);
    lcd.print(promptLine[3]);
    digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn on the pump
    digitalWrite(CLEAN_RELAY_PIN, HIGH); // Open Solenoid valve 7
    delay(PUMP_TIME); // Run for the set amount of time
    digitalWrite(CLEAN_RELAY_PIN, LOW); // Close Solenoid valve 7
    digitalWrite(PUMP_RELAY_PIN, LOW); // Turn off the pump
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
