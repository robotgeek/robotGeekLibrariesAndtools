/**********************************
 *rfiduino.cpp
 *
 *RFIDuino Library v1.0
 *
 *Trossen Robotics/RobotGeek.com
 *
 *Function file for the RFIDuino Library
 *http://www.trossenrobotics.com/rfiduino
 *http://www.trossenrobotics.com/rfiduino/library-documentation
 *
 *
 **********************************/
#include "Arduino.h"
#include "rfiduino.h"

RFIDuino::RFIDuino()
{
  //set oin modes on RFID pins
	pinMode(MOD,OUTPUT);
	pinMode(SHD,OUTPUT);
	pinMode(DEMOD_OUT,INPUT);
	pinMode(RDY_CLK,INPUT);
	
  //set SHD and MOD low to prepare for reading
	digitalWrite(SHD,LOW);
	digitalWrite(MOD,LOW);
}




  
//Manchester decode 
bool RFIDuino::decodeTag(unsigned char *buf)  
{  
    unsigned char i=0; 
    unsigned short timeCount;  
    unsigned char timeOutFlag=0; 
    unsigned char row,col;    
    unsigned char row_parity;  
    unsigned char col_parity[5];  
    unsigned char dat;      
    unsigned char searchCount=0;      
    unsigned char j;  
    while(1)  
    {                 
        timeCount=0;      
        while(0==digitalRead(DEMOD_OUT))  //watch for DEMOD_OUT to go low
        {  
            
            if(timeCount>=TIMEOUT)  //if we pass TIMEOUT milliseconds, break out of the loop
                break;
            else   
                timeCount++;        
        }     
  
        if (timeCount>=600)           
             return false;  
        else   
                timeCount=0;  
                              
        delayMicroseconds(DELAYVAL);      
        if(digitalRead(DEMOD_OUT)) 
        {             
                for(i=0;i<8;i++)  // 9 header bits
                {    
                  timeCount=0;  //restart counting
                  while(1==digitalRead(DEMOD_OUT))//while DEMOD out is high
                  {
                    if(timeCount==TIMEOUT)  
                    {       
                      timeOutFlag=1;                                      
                      break;   
                    }  
                    else   
                    timeCount++;  
                  }                                 
                                                         
                  if(timeOutFlag) 
                  {  
                     break;  
                  }  
                  else  
                  {                            
                     delayMicroseconds(DELAYVAL);       
                      if( 0==digitalRead(DEMOD_OUT) )                                                                                                          
                           break;  
                  }                    
                }//end for loop

                if(timeOutFlag)
                {       
                        timeOutFlag=0;  
                        return false;  
                }  
      
                if(i==8)  //Receive the data
                {     
                    timeOutFlag=0;  
                    timeCount=0;     
                    while(1==digitalRead(DEMOD_OUT))
                    {            
                            if(timeCount==TIMEOUT)  
                            {                         
                                    timeOutFlag=1;  
                                    break;      
                            }  
                            else  
                            {  
                                    timeCount++;  
                            }     
                                              
                            if(timeOutFlag)      
                            {  
                                    timeOutFlag=0;                                            
                                    return false;  
                            }  
                    }  
                  
                    col_parity[0]=col_parity[1]=col_parity[2]=col_parity[3]=col_parity[4]=0;   
                    for(row=0;row<11;row++)   
                    {  
                            row_parity = 0;  
                            j = row>>1;
                            for(col=0,row_parity=0;col<5;col++) 
                            {  
                                 delayMicroseconds(DELAYVAL); 
                                 if(digitalRead(DEMOD_OUT))  
                                        dat=1;  
                                    else  
                                        dat=0; 
                             
                                  if(col<4&&row<10)   
                                  {  
                                      buf[j] <<= 1;  
                                      buf[j] |= dat;                                                
                                  }  
                              
                                  row_parity += dat;      
                                  col_parity[col] += dat;  
                                  timeCount=0;                 
                                  while(digitalRead(DEMOD_OUT)==dat)  
                                  { 
                                       if(timeCount==TIMEOUT)       
                                       {     
                                         timeOutFlag=1;  
                                         break;            
                                       }  
                                       else                                                     
                                         timeCount++;  
                                              
                                    }                                         
                                    if(timeOutFlag)                                 
                                      break;   
                            }  
                           
                            if(row<10)
                            {  
                               if((row_parity&0x01)||timeOutFlag) //Row parity 
                                    {
                                            timeOutFlag=1;   
                                            break;          
                                    }  
                            }      
                    }  
                      
                                   
                    if( timeOutFlag||(col_parity[0]&0x01)||(col_parity[1]&0x01)||(col_parity[2]&0x01)||(col_parity[3]&0x01) )  //Column parity 
                    {                                                  
                            timeOutFlag=0;                               
                            return false;  
                    }   
                    else   
                    {                             
                            return true;  
                    }  
                }//end if(i==8)             
                 return false;  
        }//end if(digitalRead(DEMOD_OUT))  
    }
};



void RFIDuino::errorSound(int buzzer)  
{  
	tone(buzzer, 1300,500);
    delay(250);
    noTone(buzzer);
    delay(250);
         
    tone(buzzer, 1300,1000);
    delay(250);
    noTone(buzzer);
    delay(250);
       
    tone(buzzer, 1300,1000);
    delay(250);
    noTone(buzzer);
    delay(250);

};



void RFIDuino::successSound(int buzzer)  
{  

	tone(buzzer, 3500,1000);
    delay(165);
    noTone(buzzer);
  
    tone(buzzer, 4000,1000);
    delay(165);
    noTone(buzzer);
    
    tone(buzzer, 4500,1000);
    delay(165);
    noTone(buzzer);
    delay(165);

};


bool RFIDuino::compareTagData(byte *tag_data_1,byte *tag_data_2)  
{  
	
	for(int j=0;j<5;j++)                    
    {
		if (tag_data_1[j] != tag_data_2[j])
        {
			   return false; //if any of the ID numbers are not the same, return a false
		
        }
		
	}

			return true;  //all id numbers have been verified


}






void RFIDuino::transferToBuffer(byte *tag_data,byte *tag_data_buffer)  
{  
	
	for(int j=0;j<5;j++)                    
	
    {
		tag_data_buffer[j] = tag_data[j];
		}



}





