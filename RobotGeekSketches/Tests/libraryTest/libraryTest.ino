/* Include several libraries to check if the RobotGeek Tools and Libraries have been installed correctly*/
#include <RFIDuino.h>

#include <ServoEx.h>

#include <RobotGeekLCD.h>

#include <ArduinoNunchuk.h>

#include <Wire.h>

RobotGeekLCD lcd;
RFIDuino myrfid(1.2);  
ArduinoNunchuk nunchuk = ArduinoNunchuk();
ServoEx myservo; 



void setup()
{
    lcd.init();

}
void loop()
{
}
