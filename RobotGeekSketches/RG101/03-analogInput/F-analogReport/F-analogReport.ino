

unsigned long reportTime;
int reportInterval = 1000;
int numberOfAnalogs = 5;

//===================================================================================================
// Setup 
//====================================================================================================
void setup() 
{
   Serial.begin(9600);
   Serial.println("Analog Report");
}

void loop() 
{
  

    if(millis() - reportTime > reportInterval)
    {
      reportTime = millis();
     
      for(int i = 0; i< numberOfAnalogs; i++)
      {
        Serial.print(" Analog ");
        Serial.print(i);
        Serial.print(":");
        Serial.println(analogRead(i));      
      }
    }
  
  }


