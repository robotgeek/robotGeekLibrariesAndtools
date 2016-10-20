//*********************************************
//*                 Snoozebot                 *
//*                                           *
//* This is a simple, useless machine that    *
//* will hit the snooze button on your alarm  *
//* the second it hears it go off.            *
//*********************************************

const int SOUND_SENSOR_PIN = 0; //DFRobot Analog Sound Sensor on Analog 0
const int PUNCH_RELAY_PIN = 2;  //RobotGeek Relay with Solenoid on Digital 2

int soundValue; //variable for storing the analogRead from the Sound Sensor

void setup() 
{
  pinMode(PUNCH_RELAY_PIN, OUTPUT);   //set Relay pin to output
  digitalWrite(PUNCH_RELAY_PIN, LOW); //start relay pin off
  //Analog Inputs do not need to be defined in setup
}

void loop() 
{
  soundValue = analogRead(SOUND_SENSOR_PIN); 
  //once per cycle, read the analog value from the sound sensor and store in the soundValue variable

  if(soundValue > 175) //if the sound value variable is higher than 175 (on a scale of 0-255)
  {
    digitalWrite(PUNCH_RELAY_PIN, HIGH); //activate solenoid
    delay(3000);                         //for 3 seconds
    digitalWrite(PUNCH_RELAY_PIN, LOW);  //deactivate solenoid
    delay(1000);                         //for 1 second
    digitalWrite(PUNCH_RELAY_PIN, HIGH); //activate solenoid
    delay(100);                          //for 100ms
    digitalWrite(PUNCH_RELAY_PIN, LOW);  //deactivate solenoid
    delay(100);                          //for 100ms    
    digitalWrite(PUNCH_RELAY_PIN, HIGH); //activate solenoid
    delay(100);                          //for 100ms
    digitalWrite(PUNCH_RELAY_PIN, LOW);  //deactivate solenoid
    delay(100);                          //for 100ms    
    digitalWrite(PUNCH_RELAY_PIN, HIGH); //activate solenoid
    delay(100);                          //for 100ms
    digitalWrite(PUNCH_RELAY_PIN, LOW);  //deactivate solenoid
    delay(100);                          //for 100ms
  }
  else //in any other case than the soundValue being greater than 175
  {
    digitalWrite(PUNCH_RELAY_PIN, LOW); //deactivate solenoid
  }
}
