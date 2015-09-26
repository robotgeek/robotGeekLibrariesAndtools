/***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | |  Digital/Analog Input Demo    | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  The following sketch will use the RobotGeekLCD library to print
 *  the values of a pushbutton, a Knob and a Joystick to the LCD
 *
 *  Products
 *    http://www.robotgeek.com/robotgeek-geekduino-sensor-kit
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
 *    The state of value of each sensor will be displayed to the LCD
 *    B:Button
 *    K:Knob
 *    X:Joystick Horizontal
 *    Y:Joystick Vertical 
 * 
 *  References
 *      RobotGeek LCD Documentation http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
 *      RobotGeek Libraries and Tools (Included LCD Library) https://github.com/trossenrobotics/robotGeekLibrariesAndtools/archive/master.zip
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


RobotGeekLCD lcd;   // create a robotgeekLCD object named 'lcd'

boolean buttonState;         //holds the current HIGH/LOW state of the button
int knobValue;               //holds the current value of the knob
int joystickHorizontalValue; //holds the current value of the horizontal joystick
int joystickVerticalValue;   //holds the current value of the vertical joystick

//setup() runs one time
void setup() 
{ 
  pinMode(BUTTON_PIN, INPUT);//initialze digital pushbutton on pin BUTTON_PIN

   //analog input do not need to be initialized

  lcd.init();      // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
    
  lcd.print("RobotGeek LCD ");  // Print a message to the LCD. - the cursor is at the defualt (0,0) position, first character in the first row
  lcd.setCursor(0, 1);          //move the cursor to Column 0 in row 1 - i.e. the first character in the second row
  lcd.print("Input Demo");      // Print a message to the LCD
  delay(2000);                  //wait for 2000ms, 2 seconds
  lcd.clear();                  //clear the LCD to get ready to display the input data
}

//loop() runs forever
void loop() 
{
  buttonState = digitalRead(BUTTON_PIN);  //read the current state of the button on digital pin BUTTON_PIN and store the value in the buttonState variabl
  
  knobValue = analogRead(KNOB_PIN);  //read the value of the analog input on analog pin KNOB_PIN and store it in knobValue
  delay(5);  //short delay to allow the Analog to Digital Converter to recover before reading the next analog value
  joystickHorizontalValue = analogRead(JOYSTICK_PIN_HORIZONTAL);  //read the value of the analog input on analog pin JOYSTICK_PIN_HORIZONTAL and store it in joystickHorizontalValue
  delay(5);  //short delay to allow the Analog to Digital Converter to recover before reading the next analog value
  joystickVerticalValue = analogRead(JOYSTICK_PIN_VERTICAL);  //read the value of the analog input on analog pin JOYSTICK_PIN_VERTICAL and store it in joystickVerticalValue
  delay(5);  //short delay to allow the Analog to Digital Converter switch
   
  lcd.setCursor(0, 0);  //manually move the cursor to (0,0) first character, first row (Upper left quadrant)
  
  lcd.print("B:");     //print the label for the button value
  
  //check the button state
  if(buttonState == HIGH)
  {
    lcd.print("ON "); //when buttonState is HIGH (pressed) print 'ON '. The extra space will overwrite the last 'F' in 'OFF' when  transitioning from 'OFF' to 'ON '
  }
  else
  {
   lcd.print("OFF");  //if the buttonState is not HIGH, it will be LOW, so the LCD should display 'OFF'
  }
  
  lcd.setCursor(8, 0); //manually set the LCD to (8,0) - 9th character in the first row (Upper right quadrant)
  lcd.print("K:");     //print the label for the Knob value
  lcd.print(knobValue);//print the actual knob value
  lcd.print("   ");    //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
  
  lcd.setCursor(0, 1);  //manually set the LCD to (8,0) - 9th character in the first row(Lower left quadrant)
  lcd.print("X:");      //print the label for the horizontal joystick value
  lcd.print(joystickHorizontalValue);//print the actual joystick value
  lcd.print("   ");     //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
 
  lcd.setCursor(8, 1);  //manually set the LCD to (8,1) - 9th character in the second row(Lower right quadrant)
  lcd.print("Y:");      //print the label for the vertical joystick value
  lcd.print(joystickVerticalValue);//print the actual joystick value
  lcd.print("   ");     //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
}
