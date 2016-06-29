/*
 Basic Kit Test
 Control the LED by pressing the button.
 Control the servo by turning the knob.

Button - Digital Pin 2
Servo - Digital Pin 3
LED - Digital Pin 13
Knob - Analog Pin 0

 
 */
#include <Servo.h>

// constants won't change. They're used here to
// set pin numbers:

const int ANALOG_PIN = 0;
const int SERVO_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int SERVO_MIN = 0;
const int SERVO_MAX = 180;
const int SERVO_CENTER = 90;
const int BUTTON_PIN = 2;     // the number of the pushbutton pin
const int LED_PIN =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int analogSensorValue;    //the raw value read from the analog sensor
int servoValue;           //holds the current PWM value (0-255)\

Servo servo1;             //create servo object, 'servo1'

void setup() {
 
  pinMode(LED_PIN, OUTPUT); // initialize the LED pin as an output:
  pinMode(BUTTON_PIN, INPUT);// initialize the pushbutton pin as an input:
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN

  

  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LED_PIN, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED_PIN, LOW);
  }
  
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 
  
  servoValue = map(analogSensorValue, 0, 1023, SERVO_MAX, SERVO_MIN);  //the map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values
  servo1.write(servoValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input
  delay(10);  //short delay to account for servo movement

  
}
