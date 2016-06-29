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
 * 
 *  References
 *      RobotGeek LCD Documentation http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/57-robotgeek-i2c-lcd-getting-started-guide
 *      RobotGeek Libraries and Tools (Included LCD Library) https://github.com/trossenrobotics/robotGeekLibrariesAndtools/archive/master.zip
 *  
 ***********************************************************************************/

#include <Wire.h>              //include the I2C Wire library - needed for communication with the I2C chip attached to the LCD  as well as the OLDE 
#include <RobotGeekLCD.h>      // include the RobotGeekLCD library
#include <Adafruit_NeoPixel.h> //neopixel library for neopixel ring
#include <SeeedGrayOLED.h>     //96x96 OLED libraru
#include <avr/pgmspace.h>      //PROGMEM library for storing variables in flash
#include <TimerOne.h>          //Timerone lets us use the clock function
#include "TM1637.h"            //4-digit display library
#define ON 1
#define OFF 0

//define analog input pins for knobs
const int  KNOB_PIN_0 = 0;
const int  KNOB_PIN_1 = 1;

//define digital input pin for buttons
const int  BUTTON_PIN_0 = 4;
const int  BUTTON_PIN_1 = 7;
//define digital output pin for leds
const int LED_PIN_0 = 5;
const int LED_PIN_1 = 6;
const int LED_PIN_2 = 9;
const int LED_PIN_3 = 10;

const int  CLK = 2;//clock signal for 4-segment displsy
const int  DIO = 3 ;//data signal for 4-segment display


const int NEOPIXEL_PIN  = 12; // neopixel pin
const int NUMPIXELS = 16;   //number of pixels on neopixel ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //start neopixel ring
TM1637 tm1637(CLK,DIO); //start 4-digit display
RobotGeekLCD lcd;   // create a robotgeekLCD object named 'lcd'

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;

//values for leds. 0/1 will be binrary on//off. 2/3 will be 0-255 for PWM signal
int led0Value;
int led1Value;
int led2Value;
int led3Value;


int knob0Value;               //holds the current value of the knob
int knob1Value;               //holds the current value of the knob

//on/off values for buttons
int button0Value;
int button1Value;

//top neopixel thatis on
int neoPixelOn = -1;
int colorFromAnalog; //0-255 color value from analog sensor

//update variables used to limit refresh rate on displays
unsigned long lastUpdateTime;
int updateInterval = 10 ;//10ms refresh rate

//RG logo to shown on OLED
//See "Makle A 96x96 image.zip" on https://github.com/Seeed-Studio/OLED_Display_96X96  for more info
static const unsigned char RGLogo[] PROGMEM = 
 {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xE0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x60, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x06, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x8C, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x31, 0xC0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x06, 0x1C, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0E, 0x1C, 0x38, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x24, 0x2C, 0x30,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3C, 0x34, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x38, 0x40, 0x0E, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x30, 0xE0, 0x06, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xC0, 0x07, 0x0C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xC0, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xC1, 0x80, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC3, 0x80, 0x01, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x87, 0x80, 0x01, 0xE3,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x87, 0x80, 0x01, 0xE1, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x03, 0x40, 0x07, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
0x00, 0xFF, 0xFF, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x3F, 0xFC, 0x00,
0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x1F, 0xF8, 0x00, 0x60, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0C, 0x00, 0x1F, 0xF8, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
0x00, 0x0B, 0xB0, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x07, 0xC0, 0x00,
0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x07, 0xC0, 0x00, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x70, 0x00, 0x07, 0xC0, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
0x00, 0x03, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//setup() runs one time
void setup() 
{ 
  pinMode(BUTTON_PIN_0, INPUT);//initialze digital pushbutton on pin BUTTON_PIN
  pinMode(BUTTON_PIN_1, INPUT);//initialze digital pushbutton on pin BUTTON_PIN

  //set LEDs to outputs
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
   //analog input do not need to be initialized

  lcd.init();      // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.print("RobotGeek LCD ");  // Print a message to the LCD. - the cursor is at the defualt (0,0) position, first character in the first row
  lcd.setCursor(0, 1);          //move the cursor to Column 0 in row 1 - i.e. the first character in the second row
  lcd.print("Input Demo");      // Print a message to the LCD
   
  pixels.begin(); // This initializes the NeoPixel library.

  SeeedGrayOled.init();             //initialize SEEED OLED display
  SeeedGrayOled.clearDisplay();     //Clear Display.
  SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode

  SeeedGrayOled.drawBitmap(RGLogo,96*48/8);   //  Draw binary Bitmap (96 pixels *96 pixels  / 8) bytes

  SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
  
  SeeedGrayOled.setTextXY(6,0);  //set Cursor to ith line, 0th column
  SeeedGrayOled.setGrayLevel(5); //Set Grayscale level. Any number between 0 - 15.
  SeeedGrayOled.putString("Display Kit"); //Print Hello World
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  

   lcd.clear();                  //clear the LCD to get ready to display the input data

}

//loop() runs forever
void loop() 
{
  //only run display function if updateInterval ms has passed
  if(millis() - lastUpdateTime > updateInterval)
  {   
    setOLED(); //update OLED
    setLCD();  //update LCD
    setNeoPixel(); //update neopixel
    lastUpdateTime = millis();//reset timer
  }
  //update 4-digit display if update has completed
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }

  
  knob0Value = analogRead(KNOB_PIN_0);  //read the value of the analog input on analog pin KNOB_PIN and store it in knobValue
  delay(5);  //short delay to allow the Analog to Digital Converter to recover before reading the next analog value
  knob1Value = analogRead(KNOB_PIN_1);  //read the value of the analog input on analog pin KNOB_PIN and store it in knobValue
  delay(5);  //short delay to allow the Analog to Digital Converter to recover before reading the next analog value

  //map from the knob value (0-1023) to the number of total pixels
  neoPixelOn = map(knob0Value, 0 , 1023, 0, NUMPIXELS) ;
  
  //map from the knob value (0-1023) to a 0-255 value for color
  colorFromAnalog =map(knob1Value, 0 , 1023, 0, 255) ;

  //read button values
  button0Value = digitalRead(BUTTON_PIN_0);
  button1Value = digitalRead(BUTTON_PIN_1);

  //map analog values for PWM signal on LEDs
  led0Value = map(knob0Value, 0, 1023, 0, 255);
  led1Value = map(knob1Value, 0, 1023, 0, 255);

  //read remaining LED values as binary on/off
  led2Value = button0Value;
  led3Value = button1Value;

  //PWM write
  analogWrite(LED_PIN_0,led0Value);
  analogWrite(LED_PIN_1,led1Value);

  //digitalWrite
  digitalWrite(LED_PIN_2,led2Value);
  digitalWrite(LED_PIN_3,led3Value);

  
}

void setNeoPixel()
{
   //go through each pixel
   for(int i=0;i<NUMPIXELS;i++)
   {
    //turn pixels on if they are lower than the 'neopixelon'
    if(i <= neoPixelOn)
    {
      pixels.setPixelColor(i, Wheel(colorFromAnalog)); // set color using the Wheel function based on the analog sensor
     }
    else
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // rgb color 0,0,0 is off
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
   }
}

void setLCD()
{
  
  lcd.setCursor(0, 0);  //manually move the cursor to (0,0) first character, first row (Upper left quadrant)
  
  lcd.print("B0:");     //print the label for the button value
  
  //check the button state
  if(button0Value == HIGH)
  {
    lcd.print("ON "); //when buttonState is HIGH (pressed) print 'ON '. The extra space will overwrite the last 'F' in 'OFF' when  transitioning from 'OFF' to 'ON '
  }
  else
  {
   lcd.print("OFF");  //if the buttonState is not HIGH, it will be LOW, so the LCD should display 'OFF'
  }

  lcd.setCursor(8, 0); //manually set the LCD to (8,0) - 9th character in the first row (Upper right quadrant)
  lcd.print("B1:");     //print the label for the button value

  if(button1Value == HIGH)
  {
    lcd.print("ON "); //when buttonState is HIGH (pressed) print 'ON '. The extra space will overwrite the last 'F' in 'OFF' when  transitioning from 'OFF' to 'ON '
  }
  else
  {
   lcd.print("OFF");  //if the buttonState is not HIGH, it will be LOW, so the LCD should display 'OFF'
  }
  

  lcd.setCursor(0, 1);  //manually set the LCD to (0,1) - firstc haracter in the second row(Lower left quadrant)
  lcd.print("K0:");      //print the label for the horizontal joystick value
  lcd.print(knob0Value);//print the actual joystick value
  lcd.print("   ");     //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
 
  lcd.setCursor(8, 1);  //manually set the LCD to (8,1) - 9th character in the second row(Lower right quadrant)
  lcd.print("K1:");      //print the label for the vertical joystick value
  lcd.print(knob1Value);//print the actual joystick value
  lcd.print("   ");     //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)

}

void setOLED()
{
  

  SeeedGrayOled.setGrayLevel(12); //Set Grayscale level. Any number between 0 - 15.
  SeeedGrayOled.deactivateScroll(); //no scrolling
  SeeedGrayOled.setTextXY(10,0);  //set Cursor to 10th line, 0th column
    SeeedGrayOled.putString("NeoPixel:"); //Print label
  SeeedGrayOled.putNumber(neoPixelOn); //Print neopizel number
  SeeedGrayOled.putString(" "); //print space

  //you can uncomment code to get more display, though it may slow the rest of the code
//  SeeedGrayOled.setTextXY(1,0);  //set Cursor to ith line, 0th column
//  
//  SeeedGrayOled.putString("Knob0:"); //Print Hello World
//  SeeedGrayOled.putNumber(knob0Value); //Print Hello World
//  if(knob0Value < 10)
//  {
//    
//  SeeedGrayOled.putString("   ");  
//  }
//  else if(knob0Value < 100)
//  {
//    
//    SeeedGrayOled.putString("  ");  
//  }
//  else if(knob0Value < 1000)
//  {
//    
//    SeeedGrayOled.putString(" ");
//  }
//  
//  SeeedGrayOled.setTextXY(2,0);  //set Cursor to ith line, 0th column
//  
//  SeeedGrayOled.putString("Knob1:"); //Print Hello World
//  SeeedGrayOled.putNumber(knob1Value); //Print Hello World
//  if(knob1Value < 10)
//  {
//    
//  SeeedGrayOled.putString("   ");  
//  }
//  else if(knob1Value < 100)
//  {
//    
//    SeeedGrayOled.putString("  ");  
//  }
//  else if(knob1Value < 1000)
//  {
//    
//    SeeedGrayOled.putString(" ");
//  }
//
//  
//  SeeedGrayOled.setTextXY(3,0);  //set Cursor to ith line, 0th column
//  
//  SeeedGrayOled.putString("Button 0:"); //Print Hello World
//  SeeedGrayOled.putNumber(button0Value); //Print Hello World
//  
//  SeeedGrayOled.setTextXY(4,0);  //set Cursor to ith line, 0th column
//  SeeedGrayOled.putString("Button 1:"); //Print Hello World
//  SeeedGrayOled.putNumber(button1Value); //Print Hello World
//


}

//timing intterupt to keep track of time for 4-digit display
void TimingISR()
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;  
  }
 // Serial.println(second);
  ClockPoint = (~ClockPoint) & 0x01;
}
//update 4-digit display
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF); 
  TimeDisp[0] = minute / 10;
  TimeDisp[1] = minute % 10;
  TimeDisp[2] = second / 10;
  TimeDisp[3] = second % 10;
  //for hour/minute clock
//  TimeDisp[0] = hour / 10;
//  TimeDisp[1] = hour % 10;
//  TimeDisp[2] = minute / 10;
//  TimeDisp[3] = minute % 10;
  Update = OFF;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

