/*******************************************************************************
 *                      RobotGeek Geekbot Danger Rover
 *   |o|                      
 *   |o|                      
 *  _|o|  __________                 
 * |_|o| | _______  /_           
 * |_|o\ | ///////  _O) -  -  >PEW PEW<  o   o   
 *   |__||__________\           
 *  _|___|_|______|_|_                       
 *   |              |                         
 *   |              |                         
 *  _|______________|_
 *   |              |
 *   |     ___      |
 *  _|____/___\ ____|_
 *   \_/  \___/   \_/
 *
 *
 *  Wiring
 *
 *    Rotation Knob - Analog Pin 0
 *    Left Servo - Digital Pin 10
 *    Right Servo - Digital Pin 11
 *    Buzzer - Digital Pin 12
 *    IR Receiver - Digital Pin 2
 *    Right LED - Digital Pin 4
 *    Left LED - Digital Pin 7
 *
 *    Jumper for pins 9/10/11 should be set to 'VIN'
 *    Jumper for pins 3/5/6 should be set to '5V'
 *
 *  Control Behavior:
 *  Pressing directional button(s) (Up, Down, Left, Right) will drive the Geekbot.
 *  Pressing Select will trim the robot's drive to the left, Start will trim the drive right.
 *  Pressing TA starts the firing motor.
 *  Pressing A releases the balls from the hopper tube.
 *
 *******************************************************************************/

//Includes
#include <Servo.h>
#include <IRGamepad.h>
#include <PiezoEffects.h>

//Pin Constants
const int TRIM_KNOB_PIN = 0;
const int BUZZER_PIN = 12;
const int LED_RIGHT_PIN = 4;
const int LED_LEFT_PIN = 7;
const int LEFT_SERVO_PIN = 10;
const int RIGHT_SERVO_PIN = 11;
const int GAMEPAD_INPUT_PIN = 2;
const int FIRE_RELAY_PIN = 8;
const int LOUD_RELAY_PIN = 3;
const int HOLD_RELAY_PIN = 5;

boolean toggle = true;

//Speed constants for servo wheel speeds in microseconds
const int CCWMaxSpeed = 1750; //Left wheel forward speed
const int CCWMedSpeed = 1660;
const int CCWMinSpeed = 1580;
const int CWMaxSpeed = 1250; //Right wheel forward speed
const int CWMedSpeed = 1300;
const int CWMinSpeed = 1400;
const int ServoStopSpeed = 1500; //Servo pulse in microseconds for stopped servo
const int ServoRotateSpeedHigh = 50; //For in place rotation. Applied to CW and CCW_MIN_SPEEDs
const int ServoRotateSpeedLow = 25; //For in place rotation. Applied to CW and CCW_MIN_SPEEDs
const int MaxTrimAdjustment = 100; //Limit rotation knob trim effect in microseconds

//Gamepad constants
const unsigned long gamepadTimeout = 250; //Milliseconds to wait without control input for stopping robot (150 minimum)
const bool useModeB = false; //Set to true if your controller is switched to mode B

//Gamepad control
IR_Gamepad myGamepad(GAMEPAD_INPUT_PIN, useModeB); //IR Gamepad object
unsigned long gamepadCommandTimestamp = millis(); //Milliseconds since last command was received

//Servo control
enum SpeedSelections
{
  SPEED_MIN,
  SPEED_MED,
  SPEED_MAX
};
Servo servoLeft, servoRight; //Wheel servo objects
int servoRotateSpeed = ServoRotateSpeedHigh; //For rotating in place (controller selectable) default HIGH
int servoDriveTurningSpeed = 70; //For turning while driving (controller selectable) default 70 (microseconds)
int servoSpeedLeft = ServoStopSpeed; //Left servo speed to be sent to servo
int servoSpeedRight = ServoStopSpeed; //Right servo speed to be sent to servo
int leftFwdSpeed = CCWMaxSpeed; //Currently selected left forward speed
int leftRevSpeed = CWMaxSpeed; //Currently selected left reverse speed
int rightFwdSpeed = CWMaxSpeed; //Currently selected right forward speed
int rightRevSpeed = CCWMaxSpeed; //Currently selected right reverse speed
int currentSpeed = SPEED_MAX; //Currently selected speed from SpeedSelections enumeration

//Wheel speed trim control
int wheelSpeedTrim = 0; //Current wheel speed trim from rotation knob
int wheelSpeedTrimFromGamepad = 0; //Gamepad selectable wheel speed trim
void updateDriveTrim()
{
  int knob_value = analogRead( TRIM_KNOB_PIN );
  wheelSpeedTrim = map( knob_value, 0, 1023, -MaxTrimAdjustment, MaxTrimAdjustment );
}

//Piezo effects (sounds)
PiezoEffects mySounds( BUZZER_PIN ); //PiezoEffects object

void setup()
{
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FIRE_RELAY_PIN, OUTPUT);
  pinMode(HOLD_RELAY_PIN, OUTPUT);
  pinMode(LOUD_RELAY_PIN, OUTPUT);
  digitalWrite(LED_LEFT_PIN, HIGH);
  digitalWrite(LED_RIGHT_PIN, HIGH);
  digitalWrite(FIRE_RELAY_PIN, LOW);
  digitalWrite(LOUD_RELAY_PIN, LOW);
  digitalWrite(HOLD_RELAY_PIN, LOW);

  Serial.begin(38400);

  servoLeft.attach(LEFT_SERVO_PIN);
  servoRight.attach(RIGHT_SERVO_PIN);
  servoLeft.writeMicroseconds(servoSpeedLeft);
  servoRight.writeMicroseconds(servoSpeedRight);

  myGamepad.enable();

  Serial.println("Geekbot V2 Start");
}

void loop()
{
  if ( myGamepad.update_button_states() )
  {
    updateDriveTrim();
    gamepadCommandTimestamp = millis();
    servoSpeedLeft = ServoStopSpeed;
    servoSpeedRight = ServoStopSpeed;

    if ( myGamepad.button_press_up() )
    {
      Serial.print( "UP" );
      servoSpeedLeft = leftFwdSpeed + wheelSpeedTrim + wheelSpeedTrimFromGamepad;
      servoSpeedRight = rightFwdSpeed + wheelSpeedTrim + wheelSpeedTrimFromGamepad;
      if ( myGamepad.button_press_left() )
      {
        Serial.print( " and LEFT" );
        servoSpeedLeft -= servoDriveTurningSpeed;
      }
      if ( myGamepad.button_press_right() )
      {
        Serial.print( " and RIGHT" );
        servoSpeedRight += servoDriveTurningSpeed;
      }
    }
    else if ( myGamepad.button_press_down() )
    {
      Serial.print( "DOWN" );
      servoSpeedLeft = leftRevSpeed;
      servoSpeedRight = rightRevSpeed;
      if ( myGamepad.button_press_left() )
      {
        Serial.print( " and LEFT" );
        servoSpeedLeft += servoRotateSpeed;
      }
      if ( myGamepad.button_press_right() )
      {
        Serial.print( " and RIGHT" );
        servoSpeedRight -= servoRotateSpeed;
      }
    }
    else if ( myGamepad.button_press_left() )
    {
      Serial.print( "LEFT" );
      servoSpeedLeft = CWMinSpeed - servoRotateSpeed;
      servoSpeedRight = CWMinSpeed - servoRotateSpeed;
    }
    else if ( myGamepad.button_press_right() )
    {
      Serial.print( "RIGHT" );
      servoSpeedLeft = CCWMinSpeed + servoRotateSpeed;
      servoSpeedRight = CCWMinSpeed + servoRotateSpeed;
    }

    if ( myGamepad.button_press_start() )
    {
      Serial.print( "START" );
      mySounds.play( soundUp );
      wheelSpeedTrimFromGamepad += 5;
      myGamepad.update_button_states();
    }
    if ( myGamepad.button_press_select() )
    {
      Serial.print( "SELECT" );
      mySounds.play( soundDown );
      wheelSpeedTrimFromGamepad -= 5;
      myGamepad.update_button_states();
    }

    if ( myGamepad.button_press_b() )
    {
      Serial.print( "B" ); //(Left button)
      if ( servoDriveTurningSpeed > 10 )
      {
        servoDriveTurningSpeed -= 10;
        mySounds.play( soundDown );
      }
      else
      {
        mySounds.play( soundUhoh );
      }
      myGamepad.update_button_states();
    }
    if ( myGamepad.button_press_tb() )
    {
      Serial.print( "TB" ); //(Top button)
      switch( currentSpeed )
      {
      case SPEED_MIN:
        //Set medium speed
        mySounds.play( soundUp );
        servoRotateSpeed = ServoRotateSpeedHigh; //Apply more change with med/max speed
        currentSpeed = SPEED_MED;
        leftFwdSpeed = CCWMedSpeed;
        leftRevSpeed = CWMedSpeed;
        rightFwdSpeed = CWMedSpeed;
        rightRevSpeed = CCWMedSpeed;
        break;
      case SPEED_MED:
        //Set maximum speed
        mySounds.play( soundUp );
        currentSpeed = SPEED_MAX;
        leftFwdSpeed = CCWMaxSpeed;
        leftRevSpeed = CWMaxSpeed;
        rightFwdSpeed = CWMaxSpeed;
        rightRevSpeed = CCWMaxSpeed;
        break;
      default:
        mySounds.play( soundUhoh );
      }
      myGamepad.update_button_states();
    }
    if ( myGamepad.button_press_a() )
    {
      Serial.print( "A" ); //(Bottom button)
      
      digitalWrite(HOLD_RELAY_PIN, HIGH);
      delay(150);
      digitalWrite(HOLD_RELAY_PIN, LOW);
      digitalWrite(FIRE_RELAY_PIN, HIGH);
      delay(150);
      digitalWrite(FIRE_RELAY_PIN, LOW);
//      switch( currentSpeed )
//      {
//      case SPEED_MED:
//        //Set minimum speed
//        mySounds.play( soundDown );
//        currentSpeed = SPEED_MIN;
//        servoRotateSpeed = ServoRotateSpeedLow; //Apply less change with low speed
//        leftFwdSpeed = CCWMinSpeed + 20;
//        leftRevSpeed = CWMinSpeed - 20;
//        rightFwdSpeed = CWMinSpeed - 20;
//        rightRevSpeed = CCWMinSpeed + 20;
//        break;
//      case SPEED_MAX:
//        //Set maximum speed
//        mySounds.play( soundDown );
//        currentSpeed = SPEED_MED;
//        leftFwdSpeed = CCWMedSpeed;
//        leftRevSpeed = CWMedSpeed;
//        rightFwdSpeed = CWMedSpeed;
//        rightRevSpeed = CCWMedSpeed;
//        break;
//      default:
//        mySounds.play( soundUhoh );
//      }
      myGamepad.update_button_states();
    }
      if ( myGamepad.button_press_ta() )
      {
        Serial.print( "TA" ); //(Right button)
        if(toggle)             // Do this if toggle is true
        {
          digitalWrite(LOUD_RELAY_PIN, HIGH);
          toggle = !toggle;    // Invert toggle, making it false
        }
        else                   // Do this if toggle is false
        {
          digitalWrite(LOUD_RELAY_PIN, LOW);
          toggle = !toggle;    // Invert toggle, making it true
        }
      }
//      if ( servoDriveTurningSpeed < 200 )
//      {
//        servoDriveTurningSpeed += 10;
//        mySounds.play( soundUp );
//      }
//      else
//      {
//        mySounds.play( soundUhoh );
//      }
//      myGamepad.update_button_states();
//    }
//
//    Serial.print( " button" );
//
//    Serial.print( " PWM L: " );
//    Serial.print( servoSpeedLeft );
//    Serial.print( " R: " );
//    Serial.println( servoSpeedRight );
  }
  else if ( gamepadCommandTimestamp + gamepadTimeout < millis() )
  {
    servoSpeedLeft = ServoStopSpeed;
    servoSpeedRight = ServoStopSpeed;
  }

  servoLeft.writeMicroseconds(servoSpeedLeft);
  servoRight.writeMicroseconds(servoSpeedRight);
}
