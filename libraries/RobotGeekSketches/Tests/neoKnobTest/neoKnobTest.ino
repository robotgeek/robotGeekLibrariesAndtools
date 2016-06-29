/***********************************************************************************
 *  NeoPixel Knob Test     
 *
 *  Wiring
 *    RobotGeek Sensor Shield With Geekduino
 *      Rotational Knob - A0
 *      Neopixel - D12
 *  
 ***********************************************************************************/

#include <Adafruit_NeoPixel.h> //neopixel library for neopixel ring

const int  KNOB_PIN_0 = 0;    //analog knov pin
const int NEOPIXEL_PIN  = 12; // neopixel pin
const int NUMPIXELS = 12;     //number of pixels on neopixel ring

//colors for main ring
const int RED = 127; //0-127
const int BLUE = 0;//0-127
const int GREEN = 0;//0-127

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //start neopixel ring

int neoPixelOn = -1; //top neopixel that is on

unsigned long lastUpdateTime;//last time the neopixel was updates
int updateInterval = 100;    //interval in ms ro update neopixels.
int finalPixelColor;        //color for the 'final' neopixel, the one that the knob won't point to

//setup() runs one time
void setup() 
{    
  pixels.begin(); // This initializes the NeoPixel library.
}

//loop() runs forever
void loop() 
{
  //only run display function if updateInterval ms has passed
  if(millis() - lastUpdateTime > updateInterval)
  {   
    setNeoPixel(); //update neopixel
  }  

 
  
}

void setNeoPixel()
{
  int realPixel;  //the neopixel is offset physically, so 'real' pixel represents the actual addressed pixel

  int knob0Value = analogRead(KNOB_PIN_0);  //read the value of the analog input on analog pin KNOB_PIN and store it in knobValue

  //the knob it not totally linear at the ends, so this mapping gets a more accurate representation of knob - pixel realation
  if(knob0Value >= 1013)
  {
    neoPixelOn = 10;
  }
  else if(knob0Value < 1013 && knob0Value >= 945)
  {
    neoPixelOn = 9;
  }
  else if(knob0Value < 945 && knob0Value >= 830)
  {
    neoPixelOn = 8;
  }
  else if(knob0Value < 830 && knob0Value >= 710)
  {
    neoPixelOn = 7;
  }
  else if(knob0Value < 710 && knob0Value >= 603)
  {
    neoPixelOn = 6;
  }
  else if(knob0Value < 603 && knob0Value >= 430)
  {
    neoPixelOn = 5;
  }
  else if(knob0Value < 430 && knob0Value >= 310)
  {
    neoPixelOn = 4;
  }
  else if(knob0Value < 310 && knob0Value >= 210)
  {
    neoPixelOn = 3;
  }
  else if(knob0Value < 210 && knob0Value >= 80)
  {
    neoPixelOn = 2;
  }
  else if(knob0Value < 80 && knob0Value >= 10)
  {
    neoPixelOn = 1;
  }
  else if(knob0Value < 10)
  {
    neoPixelOn = 0;
  }
  
   //go through each pixel index
   for(int i=0;i <= NUMPIXELS - 1;i++)
   {
    realPixel = (i + 2 )%NUMPIXELS; //the neopixel is offset physically, so 'real' pixel represents the actual addressed pixel. +2 to offset, % NUMPIXELS for overflow
    //turn pixels on if they are lower than the 'neopixelon'
    if(i <= neoPixelOn)
    {
      pixels.setPixelColor(realPixel, pixels.Color(RED,GREEN,BLUE)); //set pixels on 
     }
    else
    {
      pixels.setPixelColor(realPixel, pixels.Color(0,0,0)); // rgb color 0,0,0 is off
    }
   }

    finalPixelColor = (finalPixelColor + 1)&255;  //the knob can never point ot the 'final' pixel, pixel 1. So create a 0-255 value to generate a color
    pixels.setPixelColor(1, Wheel(finalPixelColor)); // use Wheel() to generate a color from 0-255

    pixels.show(); // This sends the updated pixel color to the hardware.
    
}



//from Adafruit example
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


