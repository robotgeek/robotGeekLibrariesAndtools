

unsigned long reportTime;
int reportInterval = 100;
int numberOfAnalogs = 5;
//===================================================================================================
// Setup 
//====================================================================================================
void setup() 
{
   delay(5000);
   Serial.begin(9600);
}

void loop() 
{
  

    if(millis() - reportTime > reportInterval)
    {
      reportTime = millis();
     
      for(int i = 0; i< numberOfAnalogs; i++)
      {
        Serial.print(analogRead(i));   
        if(i != numberOfAnalogs-1)
        {
          
          Serial.print(",");   
        }
      }
      
        Serial.println("");
    }
  
  }


