/***********************************************************************************
 *      RobotGeek Temperature Sensor
 *
 *  The following sketch will read an anlog temperature sensor (TMP36) and send the
 *  temperature to the serial port.
 *    
 *  Wiring
 *    RobotGeek Sensor Shield With Geekduino/Arduino Uno/Seeeduino
 *     Analog 0 - Temperature Sensor
 *
 *
 *
 *
 ***********************************************************************************/

const int TEMPERATURE_SENSOR_PIN = 0; //anlaog pin number for the temperature sensor

float sensorVoltage;    // voltage output by the sensor
float degreeCelcius;    // temperature, in celcius
float degreeFahrenheit; // temperatue, in farenheit
  
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); //start serial port at 9600 bits per secons
  Serial.println("RobotGeek Temperature Sensor (TMP36)"); //print a header message
}

void loop() 
{
  sensorVoltage =  analogRead(TEMPERATURE_SENSOR_PIN) * 5.0 / 1023.0; //convert analog read to voltage - divide by 1023 to get a fraction, then multiple by 5v to get actual voltage
  degreeCelcius = 100 * sensorVoltage - 50 ;  //each 10mv = 1 degree, offset by 50 degress to account for negative temperature
  //degreeCelcius = (analogRead(TEMPERATURE_SENSOR_PIN) * .48875855) - 50 ; //one line formula for analog read to temp, simplifies above 2 equations, removes need for sensorVoltage variable
  
  degreeFahrenheit = (degreeCelcius * 9.0 / 5.0) + 32; //farenheit conversion from celcius
  //degreeFahrenheit = ((analogRead(TEMPERATURE_SENSOR_PIN) * .87976539) - 58);  //one line formula for analog read to temp in farenheit, simplifies above  equations, removes need for sensorVoltage variable
  

  Serial.print("Sensor Voltage:");
  Serial.print(sensorVoltage);
  
  Serial.print(" Celcius:");
  Serial.print(degreeCelcius);
  Serial.print(" Fahrenheit:");
  Serial.print(degreeFahrenheit);
  Serial.println("°");

  delay(1000); //only read/display every second to prevent serial monitor overflow. Remove this for non-serial code. 

}
