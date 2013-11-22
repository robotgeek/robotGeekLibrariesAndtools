/***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | |  Custom Characters            | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  The following sketch will use the RobotGeekLCD library to print
 *  print "I <heart> Arduino!" , 8 custom characters, and several rudimentary animatons to the LDC.
 *   http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
 *   http://www.trossenrobotics.com/robotgeek-lcd
 *
 *  The Hitachi HD44780 that runs the display is capable of storing up to 8 custom
 *  5*8 bitmap characters. Using the creatChar() function the controller can load a
 *  byte array into the HD44780 and then later call it for display.
 *
 *  Keep in mind that these characters are written to the EEPROM on the HD44780 chip. 
 *  This has 2 conseuqneces
 *  1)The custom characters are saved on the LCD even when power is lost.
 *  2)The EEPROM has a limited lifespan/number of writes. Ideally characters are
 *    written to the chip only when they need to be changed. 
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
 *     Based on Adafruit's example at
 *    https://github.com/adafruit/SPI_VFD/blob/master/examples/createChar/createChar.pde
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

/*********************************************************************
 * Custom Characters
 * Each custom character is represented by a byte array
 * that contains 8 bytes. 
 *
 * Each byte represents a new row in the character
 *(byte[0] is the top row and byte[7] is the bottom row)
 *
 * The lowest 5 bits of each byte
 * reprsent column in the row(the lowest bit is the
 * right most pixel)
 *
 * If the bit is set to '1' then the pixel will be active.
 * If the bit is set to '0' then the pixel will be inactive
 *
 * In this example the bytes are set using the '0b'  binary notation
 * This notation is handy as it can be easy to visualize the custom
 * character. The bytes could also be represented as decimal or 
 * hexadecimal values
 *
 * http://arduino.cc/en/Reference/IntegerConstants
 *********************************************************************/

//a full heart
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

//a hollowed out heart
byte heartHollow[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};

//A smiley face
byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

//a sad face
byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

//a stick figure with arms down
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

//a stick figure with arms up
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

//a robot gripper that is open
byte gripperOpen[8] = {
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00100,
  0b00100
};

//a robot gripper that is closed
byte gripperClosed[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00100,
  0b00100
};

//a bell (unused)
byte bell[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b00000,
  0b00100,
  0b00000
};

//a duck (unused)
byte duck[8] = {
  0b00000,
  0b01100,
  0b11101,
  0b01111,
  0b01111,
  0b00110,
  0b00000,
  0b00000
};


void setup() {
  
  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.init();
  //turn on the backlight
  lcd.backlight();
  
  // write a charcter to the 0 position on the HD44780 chip based on the byte array heartFull
  lcd.createChar(0, heartFull);
  // write a charcter to the 1 position on the HD44780 chip based on the byte array heartHollow
  lcd.createChar(1, heartHollow);  
  // write a charcter to the 2 position on the HD44780 chip based on the byte array smiley
  lcd.createChar(2, smiley);
  // write a charcter to the 3 position on the HD44780 chip based on the byte array frownie
  lcd.createChar(3, frownie);
  // write a charcter to the 4 position on the HD44780 chip based on the byte array gripperOpen
  lcd.createChar(4, gripperOpen);  
  // write a charcter to the 5 position on the HD44780 chip based on the byte array gripperClosed
  lcd.createChar(5, gripperClosed);  
  // write a charcter to the 6 position on the HD44780 chip based on the byte array armsDown
  lcd.createChar(6, armsDown);  
  // write a charcter to the 7 position on the HD44780 chip based on the byte array armsUp
  lcd.createChar(7, armsUp); 
  
  //set the LCD to it's home position and clear the display
  lcd.clear();

  
  // Print a message to the lcd.
  lcd.print("I "); 
  lcd.write(0);     
  lcd.print(" Arduino! ");
  
  //set the cursor to the second row, first character
  lcd.setCursor(0, 1);
  //write the 8 custom characters to the display
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);

}

void loop() 
{
  //Perform rudimentary animations based on the custom characters
  //If the animation frame rate is to high, animations may be difficult to see
  //as the LCD 'fades' from one frame to the next
  
  /*********FIRST FRAME******************/
  //set the cursor to the second row, 11th character
  lcd.setCursor(10, 1);
  // draw the full heart:
  lcd.write((byte)0);
  
  //set the cursor to the second row, 12th character
  lcd.setCursor(11, 1);
  // draw the smiley face:
  lcd.write(2);
  
  //set the cursor to the second row, 13th character
  lcd.setCursor(12, 1);
  // draw the open gripper:
  lcd.write(4);
  
  //set the cursor to the second row, 14th character
  lcd.setCursor(13, 1);
  // draw the little man, arms down:
  lcd.write(6);
  
  //wait 1 second before the next frame
  delay(1000);
  
  
  /*********SECOND FRAME******************/
  //set the cursor to the second row, 11th character
  lcd.setCursor(10, 1);
  // draw the hollow heart
  lcd.write(1);
   
  //set the cursor to the second row, 12th character
  lcd.setCursor(11, 1);
  // draw the frownie face
  lcd.write(3);
   
  //set the cursor to the second row, 13th character
  lcd.setCursor(12, 1);
  // draw the closed gripper
  lcd.write(5);
  
  //set the cursor to the second row, 14th character
  lcd.setCursor(13, 1);
  // draw the little man, arms up:
  lcd.write(7);
  
  //wait 1 second before the next frame
  delay(1000);
  
}



