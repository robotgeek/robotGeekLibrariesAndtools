/*****************************************************************************************
 *    RG 101 - Serial Communication     ______
 *    Commander Reading                | >_   |   
 *                                     |      |   
 *                                     |______|   
 *                                                 
 *                              
 *  
 *    
 * For a more in depth explanation of wiring,  this code and more information on using 
 * serial communication and Arduino check out ourserial communication tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/245-robotgeek-101-serial-communication.html
 *  
 * Important Functions
 * 
 *****************************************************************************************/

#include <Commander.h>
Commander command = Commander();

byte leftV, rightV, leftH, rightH;
bool[8] buttonArray;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  Serial.begin(38400);
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  if(command.ReadMsgs() > 0)
  {
    //command.buttons;
    leftV = command.walkV;
    leftH = command.walkH;
    rightV = command.lookV;
    rightH = command.lookH;  

    if(command.buttons&BUT_R1)
    { 
      buttonArray[0] = true;
    }
    else
    {
      buttonArray[0] = false;
    }
    if(command.buttons&BUT_R2)
    { 
      buttonArray[1] = true;
    }
    else
    {
      buttonArray[1] = false;
    }
    
    if(command.buttons&BUT_R3)
    { 
      buttonArray[2] = true;
    }
    else
    {
      buttonArray[2] = false;
    }
    
    if(command.buttons&BUT_L4)
    { 
      buttonArray[3] = true;
    }
    else
    {
      buttonArray[3] = false;
    }
    
    if(command.buttons&BUT_L5)
    { 
      buttonArray[4] = true;
    }
    else
    {
      buttonArray[4] = false;
    }
    
    if(command.buttons&BUT_L6)
    { 
      buttonArray[5] = true;
    }
    else
    {
      buttonArray[5] = false;
    }
    
    if(command.buttons&BUT_RT)
    { 
      buttonArray[6] = true;
    }
    else
    {
      buttonArray[6] = false;
    }
    
    if(command.buttons&BUT_LT)
    { 
      buttonArray[7] = true;
    }
    else
    {
      buttonArray[7] = false;
    }

    
  }
  
}//go back to the first line in loop()





