/***********************************************************************************
 *             RobotGeek Firgelli Linear Actuator Control Project   
 *           Precoded Button Control - Opening a Box with a Button                
 *            _
 *           //
 *          //
 *         //o\
 *        //_\_\_____
 *       |           |
 *       |     o     |
 *       |           |
 *      |_|---------|_|
 * 
 *
 *  The following sketch will allow you to control a Firgelli Linear actuator using
 *  a button
 *
 *  Products
 *    http://www.robotgeek.com/treasure-project-box-for-arduino
 *    http://www.robotgeek.com/robotgeek-geekduino-sensor-kit
 *    http://www.robotgeek.com/p/power-supply-6vdc-2a.aspx
 *    Firgelli Mini Linear Actuators http://www.robotgeek.com/store/Search.aspx?SearchTerms=firgelli
 *    
 *  Wiring
 *    100mm Linear Actuator - Digital Pin 9 
 *
 *    Jumper for pins 9/10/11 should be set to 'VIN'
 *  
 *
 *  Control Behavior:
 *    Button is coded to set the goal position of the Linear Actuator upon press,
 *    which will either open or close the box.
 *
 ***********************************************************************************/


//Includes
#include <Servo.h> //Servo Library
#include <Bounce2.h> //Debouncing Library

//Defines
const int LINEAR_ACTUATOR_PIN = 10;        //Linear Actuator Digital Pin
const int BUTTON_PIN = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

Servo LINEARACTUATOR;  // create servo objects to control the linear actuator

int linearValue = 2000;   // current positional value being sent to the linear actuator. 

Bounce debouncer = Bounce(); // debouncing object


void setup() 
{ 
  //initialize servo/linear actuator objects
  LINEARACTUATOR.attach(LINEAR_ACTUATOR_PIN, 1050, 2000);      // attaches/activates the linear actuator as a servo object 

  // initialize the pushbutton pin as an input with internal pullup:
  pinMode(BUTTON_PIN, INPUT_PULLUP);     

  // After setting up the button, setup the Bounce instance:
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interval in ms
  
  //use the writeMicroseconds to set the linear actuators to their default positions
  LINEARACTUATOR.writeMicroseconds(linearValue); 

} 

void loop() 
{ 
    // Update the Bounce instance :
  debouncer.update();

  // Get the updated value :
  int buttonValue = debouncer.read();

  if ( debouncer.fell() ) // if the button was pressed
  {    
    if (linearValue == 1050) //if the box is set to close
    {
      linearValue = 2000; //set box to open
    }
    else if (linearValue == 2000) //if the box was set to open
    {
      linearValue = 1050; //set box to close
    }
  } 
  
  LINEARACTUATOR.writeMicroseconds(linearValue); //use the writeMicroseconds to set the actuator to the new position
} 
