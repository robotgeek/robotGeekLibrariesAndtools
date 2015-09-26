/***********************************************************************************
 *    /X++++++++++++++++++++++++++++++++++++++++++++++++++++X\
 *   //+ RobotGeek Geekduino Basic+ Experimenter's Kit Demo +\\
 *  ///X++++++++++++++++++++++++++++++++++++++++++++++++++++X\\\
 *
 *  This Demo allows the user to quickly explore the use of buttons and knobs to
 *  control PWM devices, as well as the use of buzzers, tilt sensors, joysticks,
 *  sliders, voltage dividers + FSRs, relays, and LCD screens.
 *  
 *  Wiring:
 *  Analog  Pin 0  -      RobotGeek Light Sensor 1
 *  Analog  Pin 1  -     RobotGeek Rotation Knob 2
 *  Analog  Pin 2  -            RobotGeek Slider 1
 *  Analog  Pin 3  -    RG Voltage Divider + FSR 1
 *  Analog  Pin 6  - RG Joystick 1 Horizontal Axis
 *  Analog  Pin 7  -   RG Joystick 1 Vertical Axis
 *  Digital Pin 2  -       RobotGeek Push Button 1
 *  Digital Pin 4  -       RobotGeek Push Button 2
 *  Digital Pin 7  -       RobotGeek Push Button 3
 *  Digital Pin 8  -             RobotGeek Relay 1
 *  Digital Pin 12 -       RobotGeek Tilt Switch 1
 *  Digital Pin 13 -     RobotGeek Rotation Knob 1
 *  PWM     Pin 3  -            RobotGeek Buzzer 1
 *  PWM     Pin 5  -      LCD Screen Backlight LED
 *  PWM     Pin 6  -        RobotGeek LED Driver 2
 *  PWM     Pin 9  -            FS90 Micro Servo 1
 *  PWM     Pin 10 -        RobotGeek LED Driver 1
 *  I2C  (Pin 4&5) -        RobotGeek LCD Module 1
 *
 *  Control Behavior:
 *  Rotation Knob 1 is used as an ON/OFF switch, allowing you to engage and disengage the Environmental Sensors (Light and Tilt).
 *  Button 1 allows Rotation Knob 2 to control the position of Servo 1, and Displays Servo 1's position on the LCD.
 *  Button 2 allows Slider 1 to display a bar graph and its analog value on the LCD
 *  Button 3 displays the X and Y axis positions of Joystick 1 on the LCD
 *  Tilt Switch 1 turns Relay 1 on for a second when the sensor is jostled.
 *  Voltage Divider and FSR 1 increases the pitch of the tone playing from Buzzer 1 and increases the brightness of led 1 as the pressure on FSR 1 increases.
 *
 *  Product Links:
 *  RobotGeek Geekduino Basic+ Experimenter's Kit - https://www.trossenrobotics.com/robotgeek-experimenters-kit-basic-plus
 *  RobotGeek Geekduino - http://www.trossenrobotics.com/robotgeek-geekduino
 *  RobotGeek Sensor Shield (Version 2) - http://www.trossenrobotics.com/robotgeek-sensor-shield
 *  RobotGeek Rotation Knob - http://www.trossenrobotics.com/robotgeek-rotation-knob
 *  RobotGeek Pushbutton - http://www.trossenrobotics.com/robotGeek-pushbutton
 *  RobotGeek LED Driver - http://www.trossenrobotics.com/robotgeek-led-driver
 *  FS90 Analog Micro Plastic Gear Servo - http://www.trossenrobotics.com/9g-plastic
 *  RobotGeek Large Workbench - http://www.trossenrobotics.com/robotgeek-large-workbench.aspx
 *  RobotGeek LCD w/Mount - https://www.trossenrobotics.com/robotgeek-lcd-wmount
 *  RobotGeek Slider https://www.trossenrobotics.com/robotgeek-slider
 *  RobotGeek Voltage Divider - https://www.trossenrobotics.com/robotgeek-voltage-divider
 *  0.5 Inch Force Sensing Resistor - https://www.trossenrobotics.com/store/p/6445-5-Inch-Force-Sensing-Resistor-FSR.aspx
 *  RobotGeek Relay - https://www.trossenrobotics.com/robotgeek-relay
 *  RobotGeek Buzzer - https://www.trossenrobotics.com/robotgeek-buzzer
 *  RobotGeek Light Sensor - https://www.trossenrobotics.com/robotgeek-light-sensor
 *
 ***********************************************************************************/
//Include Libraries
#include <Servo.h>        //include the servo library, allowing us to send the proper signals to servos
#include <Wire.h>         //include the I2C Wire library - needed for communication with the I2C chip attached to the LCD 
#include <RobotGeekLCD.h> //include the RobotGeekLCD library

//use #define to set the I/O numbers, since these will never change - this saves us memory while the Arduino is running

//Define Analog Input Ports
#define LIGHT1    0       //define Light Sensor 1 as LIGHT1 at Analog Pin O
#define KNOB2     1       //define Rotation Knob 2 as KNOB2 at Analog Pin 1
#define SLIDER1   2       //define Slider 1 as SLIDER1 at Analog Pin 2
#define VDFSR1    3       //define Voltage Divider with FSR as VDFSR1 at Analog Pin 3
#define JOY1H     6       //define Joystick 1 Horizontal Axis as JOY1H at Analog Pin 6
#define JOY1V     7       //define Joystick 1 Vertical Axis as JOY1V at Analog Pin 7

//Define Digital Input Ports
#define BUTTON1   2       //define Pushbutton 1 as BUTTON1 at Digital Pin 2
#define BUTTON2   4       //define Pushbutton 2 as BUTTON2 at Digital Pin 4
#define BUTTON3   7       //define Pushbutton 3 as BUTTON3 at Digital Pin 7
#define TILT1     12      //define Tilt Swtich 1 as TILT1 at Digital Pin 12
#define KNOB1     13      //define Rotation Knob 1 as KNOB1 at Digital Pin 13


//Define Digital Output Ports. Since the LEDs are on PWM ports, we can use analogWrite() on them to vary the LED intensity
#define BUZZER1   3       //define Buzzer 1 as BUZZER1 at Digital PWM Pin 3
#define BACKLIGHT 5       //define LCD Backlight Jumper as BACKLIGHT at PWM Pin 5
#define LED2      6       //define LED Driver 2 as LED2 at Digital PWM Pin 6
#define RELAY1    8       //define Relay 1 as RELAY1 at Digital Pin 8
#define SERVO1    9       //define FS90 Mini Servo as SERVO1 at Digital PWM Pin 9
#define LED1      10      //define LED Driver 1 as LED1 at Digital PWM Pin 10

//Objects
Servo myServo;            // using the servo library, create servo object myServo to control a servo 
RobotGeekLCD lcd;         // create a robotgeekLCD object named 'lcd'

// Arrays storing custom characters for the LCD

//a full box
byte boxFull[8] = 
{
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

//a full heart
byte heartFull[8] = 
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

//Integers
// variables to hold the current value of the analog sensor, a raw value from 0-1023
int light1Value = 0;      //Assume Light Sensor is low when the sketch is loaded
int knob2Value = 512;     //Assume Knob 2 is centered when the sketch is loaded
int slider1Value = 0;     //Assume slider 1 is down when the sketch is loaded
int voltDiv1Value = 0;    //Assume FSR is not being pressed when the sketch is loaded
int joy1Horizontal = 512; //Assume Joystick Horizontal axis is centered when sketch is loaded
int joy1Vertical = 512;   //Assume Joystick Vertical axis is centered when sketch is loaded

// variables to hold the current status of the button.(LOW == unpressed, HIGH = pressed)
int knob1State = LOW;     //Assume Knob 1 is off when the sketch is loaded
int button1State = LOW;   //Assume button is off when the sketch is loaded
int button2State = LOW;   //Assume button is off when the sketch is loaded
int button3State = LOW;   //Assume button is off when the sketch is loaded
int tilt1State = HIGH;    //Assume tilt swtich is off (horizontal position) when the sketch is loaded

// variables to hold mapped values for each analog sensor (having this value will allow us to easily use analogWrite()
int valueForLED1 = 0;     //Start LED1 LOW when the sketch is loaded
int valueForLED2 = 0;     //Start LED2 LOW when the sketch is loaded
int valueForSERVO1 = 90;  //Start Servo at center position when the sketch is loaded
int valueForBUZZER1 = 0;  //Start Buzzer 1 LOW when the sketch is loaded
int numberOfBlocks = 0;   //Store number of blocks for Slider Display screen

//setup function runs one time when Geekduino is powered on
void setup()
{
  // set the PWM pins as outputs:
  pinMode(LED1, OUTPUT);      //Set the pin for LED1 to output
  pinMode(LED2, OUTPUT);      //Set the pin for LED2 to output
  pinMode(RELAY1, OUTPUT);    //Set the pin for RELAY1 to output
  pinMode(BACKLIGHT, OUTPUT); //Set the pin for BACKLIGHT to output

  // initialize the pins for the pushbuttons and environmental sensors as inputs:
  pinMode(BUTTON1, INPUT);    //Set the pin for BUTTON1 to input
  pinMode(BUTTON2, INPUT);    //Set the pin for BUTTON2 to input
  pinMode(BUTTON3, INPUT);    //Set the pin for BUTTON3 to input
  pinMode(TILT1, INPUT);      //Set the pin for TILT1 to input
  pinMode(LIGHT1, INPUT);     //Set the pin for LIGHT1 to input
  
  myServo.attach(SERVO1);     // attaches the servo on pin SERVO1 to the servo object 
  
  //LCD Setup
  lcd.init();                    // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.backlight();               //turn on the backlight
  lcd.createChar(0, boxFull);    // write a charcter to the 0 position on the HD44780 chip based on the byte array boxFull
  lcd.createChar(1, heartFull);  // write a charcter to the 1 position on the HD44780 chip based on the byte array heartFull
  lcd.clear();                   //set the LCD to it's home position and clear the display
  
  // LCD Start Up message
  lcd.print("I ");          //Print the letter I with a space after it
  lcd.write(1);             //Print the fullHeart special character
  lcd.print(" RobotGeek!"); //Print a space and then RobotGeek!
  lcd.setCursor(0,1);       //Set the cursor to the first character on the second line.
  lcd.print("3");           //Print 3
  delay(1000);              //Delay for 1 second
  lcd.print(" 2");          //Print a space and then 2
  delay(1000);              //Delay for 1 second
  lcd.print(" 1");          //Print a space and then 1
  delay(1000);              //Delay for 1 second
  lcd.print(" GO!");        //Print a space and then GO!
  delay(500);               //Delay for 1 second
  lcd.clear();              //set the LCD to it's home position and clear the display
}

void loop()
{
  //use digitalRead to store the current state of the pushbutton in one of the 'buttonState' variables
  button1State = digitalRead(BUTTON1); //set the value of button1State to HIGH or LOW as read by the BUTTON1 pin.
  button2State = digitalRead(BUTTON2); //set the value of button2State to HIGH or LOW as read by the BUTTON2 pin.
  button3State = digitalRead(BUTTON3); //set the value of button3State to HIGH or LOW as read by the BUTTON3 pin.
  tilt1State = digitalRead(TILT1);     //set the value of tilt1State to HIGH or LOW as read by the TILT1 pin.
  knob1State = digitalRead(KNOB1);     //set the value of knob1State to HIGH or LOW as read by the KNOB1 pin.

  //Use analogRead to map the value of Voltage Divider 1 to Buzzer 1
  voltDiv1Value = analogRead(VDFSR1);                    //use analogread to store the current state of the analog sensor
  valueForBUZZER1 = map(voltDiv1Value, 0,1023,0,4978);   //map the Voltage Divider Value signal (which is between 0 and 1023) to a corresponding value (between 0 and 4978) for tone output.
  valueForLED1 = map(voltDiv1Value, 0,1023,0,255);       //map the knobValue signal (which is between 0 and 1023) to a corresponding value (between 0 and 255) for analogWrite()
  if (voltDiv1Value > 50)                                //set lower limit for FSR input to prevent false positive input
  {
    digitalWrite(LED1, HIGH);                            //Turn on LED1
    tone(BUZZER1, valueForBUZZER1, 100);                 //use PWM to approximate an analog signal. A value of 0 will set the buzzer to off, and a value of 4978 will set the buzzer to a high pitch tone. 
  }
  else                                                   //when the voltage divider value is 50 or lower
  {
    digitalWrite(BUZZER1, LOW);                          //Turn off BUZZER1
    digitalWrite(LED1, LOW);                             //Turn off LED1
  }

  //ROTATION KNOB 1 - ENVIRONMENTAL SENSORS ON AND OFF
  if (knob1State == LOW)          //check if the rotation knob is turned all the way to the left
  {
    analogWrite(BACKLIGHT, 255);  //Turn Backlight ON
  }
  else if (knob1State == HIGH)    //check if the rotation knob is turned all the way to the right
  {
    //LIGHT SENSOR 1 - LCD BACKLIGHT BRIGHTNESS
    light1Value = analogRead(LIGHT1);                    // reads the value of the light sensor (value between 0 and 1023) 
    light1Value = map(light1Value, 0,1024,255,0);        // scale the light sensor value from 0-1023 to 0-255 for use in the backlight
    if ((light1Value > 70) && (light1Value < 200))       // if the light sensor reads somewhere in the middle of the range
    {
      analogWrite(BACKLIGHT, light1Value);               // set the backlight brightness according to the scaled value
    }
    else if (light1Value < 71)                           // if the scaled value is lower than 71 (it is bright in the room)
    {
      analogWrite(BACKLIGHT, 0);                         // turn off the backlight
    }
    else if (light1Value > 199)                          // if the scaled value is higher than 199 (it is dark in the room)
    {
      analogWrite(BACKLIGHT, 255);                       // set the backlight to full brightness
    }
    //TILT SWITCH 1 - RELAY 1 ON AND OFF
    if (tilt1State == LOW)          //check if the tilt switch is active, turn relay on if it is inactive (sensor in side position)
    {        
      digitalWrite(RELAY1, HIGH);   //turn the relay on
    } 
    else if (tilt1State == HIGH)    //check if the tilt switch is active, turn relay on if it is inactive (sensor in side position)
    {
      digitalWrite(RELAY1, LOW);    //turn the relay off 
    }
  }

  //NO ACTIVE BUTTONS - TRY ALL THE BUTTONS!
  if (button1State == LOW && button2State == LOW && button3State == LOW) //if all the buttons are not being pressed
  {
    //Set message on the LCD screen
    lcd.setCursor(0, 0);            //manually set the LCD to (0,0) - First character in the first row 
    lcd.print("TRY ALL THE     ");  //print the label for the slider value
    lcd.setCursor(0, 1);            //manually set the LCD to (0,1) - First character in the second row 
    lcd.print("BUTTONS!        ");  //print the label for the slider value
  }

  //BUTTON 1 - ACTIVATE SERVO 1
  else if (button1State == HIGH && button2State == LOW && button3State == LOW)  //if button 1 is active, button 2 & 3 inactive
  {
    valueForSERVO1 = analogRead(KNOB2);                    // reads the value of the potentiometer (value between 0 and 1023) 
    valueForSERVO1 = map(valueForSERVO1, 0, 1023, 180, 0); // scale the knobValue signal(0 to 1023) to a corresponding servo value(180 to 0) The inverse mapping is so the servo motion matches the knob motion
    myServo.write(valueForSERVO1);                         // sets the servo position according to the scaled value
    digitalWrite(BUZZER1, LOW);
    
    lcd.setCursor(0, 0);            //manually set the LCD to (8,0) - 9th character in the first row (Upper right quadrant)
    lcd.print("      Servo     ");  //print the label for the slider value
    lcd.setCursor(0, 1);            //manually set the LCD to (8,0) - 9th character in the first row (Upper right quadrant)
    lcd.print("   Degrees:");       //print the label for the slider value
    lcd.print(valueForSERVO1);      //print the actual slider value
    lcd.print("       ");           //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
  }
  
  //BUTTON 2 - ACTIVATE SLIDER 1
  else if (button2State == HIGH && button1State == LOW && button3State == LOW)  //if button 2 is active, button 1 & 3 inactive
  {
    slider1Value = analogRead(SLIDER1);              //read the value of the analog input on analog pin SLIDER1 and store it in slider1Value
    numberOfBlocks = map(slider1Value, 0,1023,0,16); //map the analog value from the slider(0-1023) to a number of blocks to display on the lcd screen (from 0 - 16 blocks)
    valueForLED2 = map(slider1Value, 0,1023,0,255);       //map the knobValue signal (which is between 0 and 1023) to a corresponding value (between 0 and 255) for analogWrite()
    analogWrite(LED2, valueForLED2);                       //use PWM to approximate an analog signal. A value of 0 will set the LED to off, and a value of 255 will set the LED to fully on.  
    
    lcd.setCursor(0, 0);             //manually set the LCD to (0,0) - First character in the first row
    lcd.print("   Slider:");         //print the label for the slider value
    lcd.print(slider1Value);         //print the actual slider value
    lcd.print("   ");                //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
    lcd.setCursor(0, 1);             //set the cursor to column 0, line 1
                                     //(note: line 1 is the second row, since counting begins with 0):

    for(int j = 0; j< 16; j = j + 1) //set up an iterator loop. Start the integer 'j' at 0, set the limit to less than 16, and set the rule to count up by one
    {  
      if (j < numberOfBlocks)        //test 'j' against the number of blocks. if 'j' is less than the number of blocks
      {
        lcd.write(255);              //write a full block character
      }
      else                           //otherwise
      {
      lcd.print(" ");                //write a space in its place.
      }
    }
  }
  
  //BUTTON 3 - READ JOYSTICK 1
  else if (button3State == HIGH && button2State == LOW && button1State == LOW)  //if button 3 is active, button 1 & 2 inactive
  {
    joy1Horizontal = analogRead(JOY1H);   //read the value of the analog input on analog pin SLIDER1 and store it in slider1Value
    delay(5);                             //short delay to allow the Analog to Digital Converter to recover before reading the next analog value
    joy1Vertical = analogRead(JOY1V);     //read the value of the analog input on analog pin SLIDER1 and store it in slider1Value
    
    lcd.setCursor(0, 0);                  //manually set the LCD to (0,0) - First character in the first row
    lcd.print("    Joystick  ");          //print the label for the joystick value
  
    lcd.setCursor(0, 1);                  //manually set the LCD to (0,1) - first character in the second row 
    lcd.print("X:");                      //print the label for the X-axis value
    lcd.print(joy1Horizontal);            //print the actual X-axis value
    lcd.print("     ");                   //print '    '(four spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)

    lcd.setCursor(10, 1);                 //manually set the LCD to (10,1) - 11th character in the second row 
    lcd.print("Y:");                      //print the label for the Y-axis value
    lcd.print(joy1Vertical);              //print the actual Y-axis value
    lcd.print("   ");                     //print '   '(three spaces). This will clear away old text when the knobValue number goes from a high number to a low number (i.e. from a 4 digit number down to a 1 digit number)
  }
}
