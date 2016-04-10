/*
 * WiiClassy.cpp - Improved Wii Classic/Pro library for Arduino
 * 		Works with 3rd party controllers using unencrypted comm
 * 
 *
 * Based on the following projects/websites:
 *	 http://playground.arduino.cc/Main/WiiClassicController10
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 * 	 http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *	 http://www.wiili.org/index.php/Wiimote/Extension_Controllers/Classic_Controller
 */

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define GP2Y0A41SK0F 0;
#define GP2D12       1;
#define GP2Y0A02YK   2;




//initialize with default update interval
void RGSharpIr::init(int initPin, int initSensorType)
{ 

  sensorType = initSensorType;
  analogPin = initPin


}



    
int RGSharpIr::getCm()
{ 
  analogRead(analogPin);  //reade once, to discard  read
  rawValue = analogRead(analogPin);
  rawValue = max(1,rawValue); //filter out '0' so there are no divide by zero errors
  
  if(sensorType == GP2Y0A41SK0F)
  {
      //forumla from https://www.sparkfun.com/products/12728
      distanceCM = (2598.42/rawValue) - .42;

  }
  
  else if(sensorType == GP2D12)
  {
    //formula from https://www.sparkfun.com/products/242

    distanceCM = 41.543 * (((float)rawValue/1023.0) + 0.30221) ^ -1.5281;

  }
  
  else if(sensorType == GP2Y0A02YK)
  {
    //formula from https://www.sparkfun.com/products/8958

    distanceCM = 61.681 * ((float)rawValue/1023.0) ^ -1.133


  }




  return(distanceCM);
}

    
int RGSharpIr::getIn()
{ 
  analogRead(analogPin);  //reade once, to discard  read
  rawValue = analogRead(analogPin);
  return(distanceIn);
}

    
int RGSharpIr::getRaw()
{ 
  analogRead(analogPin);  //reade once, to discard  read
  rawValue = analogRead(analogPin);
  return(rawValue);
}


