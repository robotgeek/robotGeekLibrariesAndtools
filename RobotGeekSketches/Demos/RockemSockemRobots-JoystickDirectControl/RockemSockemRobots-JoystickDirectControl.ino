/***********************************************************************************
 *                      ROCK EM SOCK EM LITERAL ROBOTS
 *                           Let's duke it out!
 * This sketch will allow you to control one nearly humanoid fighting robot using
 * a joystick for aiming the pan and tilt, and one button each for throwing the fists.
 * It is dangerous to pit robots against each other, both for you and for the robots.
 * Servos will burn out under heavy load, and there is no warranty on burned out servos. 
 * Fair warning.
 * 
 * Controller:
 * Analog 0  - RobotGeek Joystick (Horizontal)
 * Analog 1  - RobotGeek Joystick (Vertical)
 * Digital 2 - RobotGeek Pushbutton    (Gripper)
 * 
 * Robot:
 * Digital 3  - RobotGeek 180 Servo (Pan)
 * Digital 5  - RobotGeek 180 Servo (Tilt)
 * Digital 6  - RobotGeek 180 Servo (Left Shoulder)
 * Digital 9  - RobotGeek 180 Servo (Right Shoulder)
 * Digital 10 - RobotGeek 180 Servo (Left Elbow)
 * Digital 11 - RobotGeek 180 Servo (Right Elbow)
 * 
 * Set both of the jumpers on the RobotGeek Sensor Shield to VIN.
 * 
 ***********************************************************************************/

#include <Servo.h>        //Include the Servo Library
#include <Bounce2.h>

Servo servo0;              //This creates an object for the Servo library, 'servo0'.
Servo servo1;              //This creates an object for the Servo library, 'servo1'.
Servo servo2;              //This creates an object for the Servo library, 'servo2'.
Servo servo3;              //This creates an object for the Servo library, 'servo3'.
Servo servo4;              //This creates an object for the Servo library, 'servo4'.
Servo servo5;              //This creates an object for the Servo library, 'servo4'.

const int ANALOG_0_PIN = 0;  // Analog Pin 0 is the first Rotation Knob in the system. This will be set to control the Base Rotation Servo on the Snapper.
const int ANALOG_1_PIN = 1;  // Analog Pin 1 is the second Rotation Knob in the system. This will be set to control the Shoulder Servo on the Snapper.

const int DIGITAL_2_PIN = 2; // Analog Pin 3 is the fourth Rotation Knob in the system. This will be set to control the Wrist Servo on the Snapper.
const int DIGITAL_4_PIN = 4; // Digital Pin 2 is the only Pushbutton in the system. This will be set to control the Gripper on the Snapper.
const int DIGITAL_7_PIN = 7; // Digital Pin 2 is the only Pushbutton in the system. This will be set to control the Gripper on the Snapper.

int current0Value, next0Value; // This makes two variables for handling the values we'll be storing to smooth out the movement.
int current1Value, next1Value; // This makes two variables for handling the values we'll be storing to smooth out the movement.

Bounce buttonLeft  = Bounce();  //debouncing
Bounce buttonRight = Bounce();  //debouncing
Bounce buttonHit   = Bounce();  //debouncing

void setup() 
{
  Serial.begin(9600); // This begins sending Serial Output at a baud rate of 9600, which can be read in the Serial Monitor in your Arduino IDE

  pinMode(ANALOG_0_PIN, INPUT);  // Setting Analog Pin 0 to Input
  pinMode(ANALOG_1_PIN, INPUT);  // Setting Analog Pin 1 to Input
  
  pinMode(DIGITAL_2_PIN, INPUT); // Setting Digital Pin 2 to Input
  buttonLeft.attach(DIGITAL_2_PIN);
  buttonLeft.interval(5); // interval in ms
  
  pinMode(DIGITAL_4_PIN, INPUT); // Setting Digital Pin 4 to Input
  buttonRight.attach(DIGITAL_4_PIN);
  buttonRight.interval(5); // interval in ms
  
  pinMode(DIGITAL_7_PIN, INPUT); // Setting Digital Pin 7 to Input
  buttonHit.attach(DIGITAL_7_PIN);
  buttonHit.interval(5); // interval in ms

  servo0.attach(3);  // This attaches the servo to the appropriate pin using the servo library.
  servo1.attach(5);  // This attaches the servo to the appropriate pin using the servo library.
  servo2.attach(6);  // This attaches the servo to the appropriate pin using the servo library.
  servo3.attach(9);  // This attaches the servo to the appropriate pin using the servo library.
  servo4.attach(10); // This attaches the servo to the appropriate pin using the servo library.
  servo5.attach(11); // This attaches the servo to the appropriate pin using the servo library.

  servo0.write(90); //Center Pan Servo
  servo1.write(90); //Center Tilt Servo
  servo2.write(90); //Center Left Shoulder
  servo3.write(90); //Center Right Shoulder
  servo4.write(0);  //Forward Left Fist
  servo5.write(180);//Forward Right Fist

  Serial.println("Starting Up..."); //Send some text over Serial
}

void loop() 
{

  next0Value = analogRead(ANALOG_0_PIN);           //Set Next0Value to the value read from Analog 0
  next0Value = map(next0Value, 120, 900, 0, 180);  //Map the value we just read from Analog 0 to a set of values that can be used for a servo.
  
  next1Value = analogRead(ANALOG_1_PIN);           //Set Next1Value to the value read from Analog 1
  next1Value = map(next1Value, 120, 900, 0, 180);  //Map the value we just read from Analog 1 to a set of values that can be used for a servo.

  buttonLeft.update();
  buttonRight.update();
  buttonHit.update();

  //Send a readout of the angles of each servo over serial 
  Serial.print("Base Angle = ");
  Serial.print(next0Value);
  Serial.println("º");

  Serial.print("Shoulder Angle = ");
  Serial.print(next1Value);
  Serial.println("º");

  /*
   * Write Values to the Base Servo
   */
  if (next0Value > current0Value)                     // If the mapped value read at Analog 0 is higher than the value read by Servo 0
  {
    for (int i = current0Value; i <= next0Value; i++) // This makes a for loop where i is the value read by Servo 0. While it is less than or equal to the mapped value of Analog 0, add 1 to current0Value.
    {
      servo0.write(i);                                // Write current0Value to Servo 0
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current0Value until it has the same value as next0Value.
  } 
  else if (next0Value < current0Value)                // If the mapped value read at Analog 0 is lower than the value read by Servo 0
  {
    for (int i = current0Value; i >= next0Value; i--) // This makes a for loop where i is the value read by Servo 0. While it is greater than or equal to the mapped value of Analog 0, subtract 1 from current0Value.
    {
      servo0.write(i);                                // Write current0Value to Servo 0
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, subtracting 1 from current0Value until it has the same value as next0Value.
  }

  /*
   * Write Values to the Shoulder Servo
   */
  if (next1Value > current1Value)                     // If the mapped value read at Analog 1 is higher than the value read by Servo 1
  {
    for (int i = current1Value; i <= next1Value; i++) // This makes a for loop where i is the value read by Servo 1. While it is less than or equal to the mapped value of Analog 1, add 1 to current1Value.
    {
      servo1.write(i);                                // Write current1Value to Servo 1
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current1Value until it has the same value as next1Value.
  } 
  else if (next1Value < current1Value)                // If the mapped value read at Analog 1 is lower than the value read by Servo 1
  {
    for (int i = current1Value; i >= next1Value; i--) // This makes a for loop where i is the value read by Servo 1. While it is greater than or equal to the mapped value of Analog 1, subtract 1 from current1Value.
    {
      servo1.write(i);                                // Write current1Value to Servo 1
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, subtracting 1 from current1Value until it has the same value as next1Value.
  }

  /*
   * Set Current Values of the Servos
   */
  current0Value = servo0.read(); // Save the position of Servo 0 to current0Value
  current1Value = servo1.read(); // Save the position of Servo 1 to current1Value
  
  int punchLeft  = buttonLeft.read();
  int punchRight = buttonRight.read();
  int tookHit    = buttonHit.read();
  delay(2); //delay for 2 milliseconds

  /*
   * Do things with the buttons
   */
   
  //Left Punch
  if ( punchLeft == HIGH ) 
  {
    servo2.write(0);
    servo4.write(90);    
  } 
  else 
  {
    servo2.write(90);
    servo4.write(0);
  }   
  
  //Right Punch
  if ( punchRight == HIGH ) 
  {
    servo3.write(180);
    servo5.write(90);    
  } 
  else 
  {
    servo3.write(90);
    servo5.write(180);
  }

  //Took Hit
  if ( tookHit == HIGH ) 
  {
    servo0.write(90); //Center Pan Servo
    servo1.write(90); //Center Tilt Servo
    servo2.write(0); //Center Left Shoulder
    servo3.write(180); //Center Right Shoulder
    servo4.write(0);  //Forward Left Fist
    servo5.write(180);//Forward Right Fist
    delay(500);
    servo0.write(90); //Center Pan Servo
    servo1.write(180); //Center Tilt Servo
    servo2.write(0); //Center Left Shoulder
    servo3.write(180); //Center Right Shoulder
    servo4.write(90);  //Forward Left Fist
    servo5.write(90);//Forward Right Fist
    delay(500);
    servo0.write(90); //Center Pan Servo
    servo1.write(180); //Center Tilt Servo
    servo2.write(180); //Center Left Shoulder
    servo3.write(0); //Center Right Shoulder
    servo4.write(0);  //Forward Left Fist
    servo5.write(180);//Forward Right Fist
    delay(10000); //Down for 10 Seconds
  } 

}
