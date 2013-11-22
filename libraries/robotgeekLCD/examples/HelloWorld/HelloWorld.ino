/***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | |  Hello World                  | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  The following sketch will use the RobotGeekLCD library to print
 *  'Hello World' to the Robotgeek LCD
 *   http://www.trossenrobotics.com/robotgeek-lcd
 *    
 *  Wiring
 *    RobotGeek Sensor Shield With Geekduino/Arduino Uno/Seeeduino
 *      The RobotGeek I2C LCD will plug directly into the 4-pin I2C port on
 *      the sensor shield using a 4-pin sensor cable. Normally the sensor cable
 *      will be plugged in with the following orientation:
 *        SCL    - Yellow
 *        SDA    - White
 *        5v/VCC - Red
 *        G/GND  - Black
 *  
 *    Geekduino/Arduino/Seeeduino 
 *       The RobotGeek I2C LCD can be plugged direcly into the pins of a 
 *        ~duino board using Female-Female jumper cables and pin couplers
 *        LCD - ~duino Pin 
 *        SCL - A5
 *        SDA - A4
 *        VCC - 5v
 *        GND - Gnd
 *        
 *    ArbotiX
 *        LCD - ~duino Pin 
 *        SCL - D16 9Pin closest to processor0
 *        SDA - D17 9Pin closest to processor0
 *        VCC - 5v Pin on D17 (Middle Pin)
 *        GND - Gnd Pin on D17(Pin closest to the edge of the board)
 *
 *
 *  Control Behavior:
 *    The Horizontal Joystick will move the Pan Servo
 *    The Vertical Joystick will move the Tilt Servo
 *    The Pushbutton  will toggle the laser mofule on/off
 *
 *  References
 *    This example and the RobotGeekLCD library is based off the Arduino
 *    LiquidCrystal Library
 *    http://www.arduino.cc/en/Tutorial/LiquidCrystal
 *    This example code is in the public domain.
 *
 *
 ***********************************************************************************/


//include the I2C Wire library - needed for communication with the I2C chip attached to the LCD manual 
#include <Wire.h> 
// include the RobotGeekLCD library
#include <RobotGeekLCD.h>

// create a robotgeekLCD object named 'lcd'
RobotGeekLCD lcd;

void setup() 
{
  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.init();
  // Print a message to the LCD.
  lcd.print("Hello, World!");
}

void loop() 
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
