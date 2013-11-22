/***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | |  Scroll                       | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  The following sketch will print "Hello World!" to the LCD and uses the
 *  scrollDisplayLeft() and scrollDisplayRight() methods to scroll the text.
 *   http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
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
 *  References
 *    This example and the RobotGeekLCD library is based off the Arduino
 *    LiquidCrystal Library and examples
 *    http://www.arduino.cc/en/Tutorial/LiquidCrystal
 *    http://arduino.cc/en/Tutorial/LiquidCrystalScroll
 *     This example code is in the public domain.
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
  delay(1000);
}

void loop() {
  // scroll 13 positions (string length) to the left 
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(500);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(500);
  }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(500);
  }
  
  // delay at the end of the full loop:
  delay(1000);

}

