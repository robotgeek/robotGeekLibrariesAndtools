/***********************************************************************************
 *    /+---------------------------------------------------+\
 *   //| RobotGeek Geekduino Basic Experimenter's Kit Demo |\\
 *  ///+---------------------------------------------------+\\\
 *
 *  This Demo allows the user to quickly explore the use of buttons and knobs to
 *  control PWM devices.
 *  
 *  Wiring:
 *  Analog  Pin 0  - RobotGeek Rotation Knob 1
 *  Analog  Pin 1  - RobotGeek Rotation Knob 2
 *  Digital Pin 2  -   RobotGeek Push Button 1
 *  Digital Pin 4  -   RobotGeek Push Button 2
 *  Digital Pin 7  -   RobotGeek Push Button 3
 *  PWM     Pin 3  -    RobotGeek LED Driver 1
 *  PWM     Pin 5  -    RobotGeek LED Driver 2
 *  PWM     Pin 9  -        FS90 Micro Servo 1
 *
 *  Control Behavior:
 *  Button 1 activates LED 2 when pressed. Button 2 runs a script on LED 2, gradually
 *  increasing brightness. Rotation Knob 1 controls the brightness of LED 1. Button 3
 *  starts the analog read of Rotation Knob 2, which controls the position of the
 *  FS90 mini servo.
 *
 *  Product Links:
 *  RobotGeek Geekduino Basic Experimenter's Kit - https://www.trossenrobotics.com/store/p/7046-RobotGeek-Geekduino-Experimenter-s-Kit-Level-2.aspx
 *  RobotGeek Geekduino - http://www.trossenrobotics.com/robotgeek-geekduino
 *  RobotGeek Sensor Shield (Version 2) - http://www.trossenrobotics.com/robotgeek-sensor-shield
 *  RobotGeek Rotation Knob - http://www.trossenrobotics.com/robotgeek-rotation-knob
 *  RobotGeek Pushbutton - http://www.trossenrobotics.com/robotGeek-pushbutton
 *  RobotGeek LED Driver - http://www.trossenrobotics.com/robotgeek-led-driver
 *  FS90 Analog Micro Plastic Gear Servo - http://www.trossenrobotics.com/9g-plastic
 *  Robot Geek Large Workbench - http://www.trossenrobotics.com/robotgeek-large-workbench.aspx
 *
 ***********************************************************************************/
// Include Libraries
#include <Servo.h> //Include the servo library, allowing us to send the proper signals to servos

// use #define to set the I/O numbers, since these will never change - this saves us memory while the Arduino is running

//define analog input ports
#define KNOB1     0      //define Rotation Knob 1 as KNOB1 at Analog Pin O
#define KNOB2     1      //define Rotation Knob 2 as KNOB2 at Analog Pin 1

//define digital input ports
#define BUTTON1   2      //define Pushbutton 1 as BUTTON1 at Digital Pin 2
#define BUTTON2   4      //define Pushbutton 2 as BUTTON2 at Digital Pin 4
#define BUTTON3   7      //define Pushbutton 3 as BUTTON3 at Digital Pin 7

//define digital output ports. Since these are PWM ports, we can use analogWrite() on them to vary the LED intensity
#define LED1      3      //define LED Driver 1 as LED1 at Digital PWM Pin 3
#define LED2      5      //define LED Driver 2 as LED2 at Digital PWM Pin 5
#define SERVO1    9      //define FS90 Mini Servo as SERVO1 at Digital PWM Pin 9

//Objects
Servo myServo;           // using the servo library, create servo object myServo to control a servo 

//Integers
// variables to hold the current value of the analog sensor, a raw value from 0-1023
int knobValue1 = 0;      //Assume Knob 1 is off when the sketch is loaded
int knobValue2 = 512;    //Assume Knob 2 is centered when the sketch is loaded

// variables to hold the current status of the button.(LOW == unpressed, HIGH = pressed)
int button1State = LOW;    //Assume button is off when the sketch is loaded
int button2State = LOW;    //Assume button is off when the sketch is loaded
int button3State = LOW;    //Assume button is off when the sketch is loaded

// variables to hold mapped values for each analog sensor (having this value will allow us to easily use analogWrite()
int valueForLED1 = 0;     //Start LED1 LOW when the sketch is loaded
int valueForLED2 = 0;     //Start LED2 LOW when the sketch is loaded
int valueForSERVO1 = 90;  //Start Servo at center position when the sketch is loaded

// variables for the LED fading script
int LED2bright = 0;      // how bright LED2 is
int LED2fadeAmount = 5;  // how many points to fade LED2 by

//setup function runs one time when Geekduino is powered on
void setup()
{
  // set the PWM pins as outputs:
  pinMode(LED1, OUTPUT);      
  pinMode(LED2, OUTPUT);        

  // initialize the pins for the pushbutton as inputs:
  pinMode(BUTTON1, INPUT);     
  pinMode(BUTTON2, INPUT); 
  pinMode(BUTTON3, INPUT);
  
  myServo.attach(SERVO1);  // attaches the servo on pin SERVO1 to the servo object 
}


//loop function runs forever after the setup() function
void loop()
{
  //use digitalRead to store the current state of the pushbutton in one of the 'buttonState' variables
  button1State = digitalRead(BUTTON1);
  button2State = digitalRead(BUTTON2);
  button3State = digitalRead(BUTTON3);

  //check if the first pushbutton is pressed, and turn the LED on as long as the button is pressed
  if (button1State == HIGH) 
  {        
    digitalWrite(LED2, HIGH);    //turn the LED on
  } 
  else 
  {
      digitalWrite(LED2, LOW);  //turn the LED off 
  }

  //check if the second pushbutton is held down, and fade light. Otherwise, nothing happens.
  if (button2State == HIGH) 
  {   
    LED2bright = LED2bright + LED2fadeAmount;  // change the brightness for next time through the loop
    analogWrite(LED2, LED2bright);             // set the brightness of pin 9
    
    // reverse the direction of the fading at the ends of the fade 
    if (LED2bright <= 0 || LED2bright >= 255)
    {
      LED2fadeAmount = -1 * LED2fadeAmount ; //inverse the sign og the fade amount. If it was previosuly adding, it will now start subtracting and vice versa 
    }      
    delay(30);  // wait for 30 milliseconds to see the dimming effect   
  }
 
  //check if the third pushbutton is pressed, and write knob value to servo. Otherwise, nothing happens.
  if (button3State == HIGH) 
  {   
    valueForSERVO1 = analogRead(KNOB2);                    // reads the value of the potentiometer (value between 0 and 1023) 
    valueForSERVO1 = map(valueForSERVO1, 0, 1023, 0, 180); // scale the knobValue signal(0 to 1023) to a corresponding servo value(0 to 180)
    myServo.write(valueForSERVO1);                         // sets the servo position according to the scaled value 
    delay(15);                                             // waits for the servo to get to the position 
  }
  else
  { 
    knobValue1 = analogRead(KNOB1);                        //use analogread to store the current state of the analog sensor
    delay(10);                                             //wait 10 milliseconds
    valueForLED1 = map(knobValue1, 0,1023,0,255);          //map the knobValue signal (which is between 0 and 1023) to a corresponding value (between 0 and 255) for analogWrite()
    analogWrite(LED1, valueForLED1);                       //use PWM to approximate an analog signal. A value of 0 will set the LED to off, and a value of 255 will set the LED to fully on.  
  }  
}
