 /***********************************************************************************
 *       ___________________________________
 *      |  _______________________________  |
 *      | |RobotGeek I2C LCD              |\|
 *      | |  RobotGeekLCD.h             | |
 *      | |                               | |
 *      | |_______________________________|/|
 *      |___________________________________|
 *
 *  This library will allow use of the RobotGeek IIC LCD
 *   http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
 *   http://www.trossenrobotics.com/robotgeek-lcd
 *     
 *	The RobotGeek IIC LCD has 3 components
 *	1)16x2 LCD
 *	2)Hitachi HD44780 LCD Driver
 *	3)pcf8574 I2C - I2C IO Expander
 *	
 *	The HD44780 is controlled by 3 control pins and 8 data pins. These pins
 *	are controlled by the pcf8574 I2C chip. By sending IIC data to this chip
 *	the controller can control the HD44780 and the LCD. The pcf8574 also gives
 *	access to the backlight.
 *
 *
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
 *     This example code is in the public domain.
 *
 *
 ***********************************************************************************/
 
#ifndef RobotGeekLCD_h
#define RobotGeekLCD_h
#define LCD_TEST 3

#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

class RobotGeekLCD : public Print {
public:
  RobotGeekLCD();
  

  void init();
    
  void begin(uint8_t address);

  void clear();
  void home();


  void noBacklight();
  void nooBacklight();
  void backlight();
  void writeIIC(uint8_t _data);
  
  
  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
  virtual size_t write(uint8_t);
  
  void command(uint8_t);
  
  //using Print::write;
private:
	//void expanderSend(uint8_t data, uint8_t backlight, uint8_t enableex, uint8_t rsex, uint8_t rwex)

  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void write4bitsData(uint8_t);
  void write4bitsCommand(uint8_t);
  void write8bits(uint8_t);
  void pulseEnable(uint8_t current);
  uint8_t _rs_pin; // LOW: command.  HIGH: character.
  uint8_t _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[8];


  uint8_t _iicLastSent;
  uint8_t _backlight;
  
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines,_currline;
  //bargrpah
  //shift increment/
  //shift decrement
  //contrast
  
};

#endif
