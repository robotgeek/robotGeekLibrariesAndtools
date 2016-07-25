/***********************************************************************************
 *
 *        .--.
 *    .-========-.
 *    | === [__] |        IR Remote Wizard
 *    | [__][__] |
 *    | o   ==== |
 *    | LILILILI |
 *    | LILILILI |
 *    | LILILILI |
 *    | LILILILI |
 *    |  __  __  |
 *    | [__][__] |
 *    | [__][][] |
 *    | [__] ==  |
 *    |      OOO |
 *    '-========-' 

 *
 *  The following sketch help you build a code block that you can copy/paste
 *  into RobotGeek IR control sketches. Load the code onto your board, then 
 *  open the Serial Monitor at 9600bps. Follow the instructions on the monitor,
 *  by sending codes from your remote to the IR reciever, then sending a character
 *  on the serial monitor to get to the next step.
 *     
 *  Wiring
 *    IR Reciever - Pin 11
 *
 *
 *ASCII Art from http://www.ascii-code.com/ascii-art/electronics/televisions.php
 *
 ***********************************************************************************/

 
#include <IRLib.h>  //include the IR library to decode data

const int RECEIVE_PIN = 11; //pin to attach the IR receiver to
const int NUMBER_OF_BUTTONS = 17; //number of buttons that the wizard will accept
const int REPEAT_CODE = 0xFFFFFFFF; //repeat code for NEC remotes

IRrecv My_Receiver(RECEIVE_PIN); //start the receiver class on pin RECEIVE_PIN
IRdecode My_Decoder;             //start the decoder class

int protocol = -1;  //int that represents protocol
bool protocolDone = false; //false if we have not read the protocol, true if we have

unsigned long ir_data[NUMBER_OF_BUTTONS]; //holds the button data - needs to be a long since the buttons are more than an integer can hold

//strings for informing users and for printing out the code block at the end
String buttonNames[NUMBER_OF_BUTTONS] ={
                          "RIGHT_BUTTON",
                          "LEFT_BUTTON",
                          "UP_BUTTON",
                          "DOWN_BUTTON",
                          "SELECT_BUTTON",
                          "ONE_BUTTON",
                          "TWO_BUTTON",
                          "THREE_BUTTON",
                          "FOUR_BUTTON",
                          "FIVE_BUTTON",
                          "SIX_BUTTON",
                          "SEVEN_BUTTON", 
                          "EIGHT_BUTTON",
                          "NINE_BUTTON",
                          "ZERO_BUTTON",   
                          "SPECIAL_1_BUTTON",   
                          "SPECIAL_2_BUTTON"            
};

 
void setup() 
{ 
  Serial.begin(9600); //start serial class
  Serial.println("Remote Wizard");//print header

  My_Receiver.No_Output();//Turn off any unused IR LED output circuit

  My_Receiver.enableIRIn(); // Start the receiver

  Serial.println("Press buttons on your remote");
  //loop while no protocol has been received
  while(protocolDone == false)
  {
    //try to read data from IR receiver
    if (My_Receiver.GetResults(&My_Decoder)) 
    {
     
      My_Decoder.decode(); //decode results
      protocol = My_Decoder.decode_type;  //get the protocol from the results
      Serial.print("    Protocol Found:");
      Serial.print(protocol, HEX);
      Serial.println(" Send any character on the serial monitor to continue");
      
      My_Receiver.resume();//resume reading
    }

    //this block will look for serial data - if any comes in, the block will discard the serial data, and set a flag to let the program progress to the next section
    if(Serial.available() && protocol != -1)
    {
      //serial data has come in, so flush the buffer
      while(Serial.available())
      {
        Serial.read();
      }
      protocolDone = true;//set the protocolDone flag to true, so that we can exit the while() loop
    }
    
  }
  
  Serial.println("Protocol Section Finished. Start Button reading.");

  //go through each button that we want to read
  for(int i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
    Serial.print("Press the button for ");
    Serial.println(buttonNames[i]);
    int buttonRead = false; //the button has not yet been read. We will only proceed if serial data comes in and buttonRead has been hcanged to true
    //loop while the button has not ben finished being read
     while(buttonRead == false)
    {
      //try to get results from receiver
      if (My_Receiver.GetResults(&My_Decoder)) 
      {
        My_Decoder.decode();//decode packet
        
        //check if the decoded protocol matches the previosuly found protocol
        if(My_Decoder.decode_type == protocol)
        {
          //make sure the code is not a repeat code for NEX
          if(My_Decoder.value != REPEAT_CODE)
          {
            ir_data[i] = My_Decoder.value;  //store code value
            Serial.print("    Button Found:");
            Serial.print(My_Decoder.value, HEX);
            Serial.println(" Send any character on the serial monitor to continue");
          }
        }
        My_Receiver.resume();//resume reading
      }

     //this block will look for serial data - if any comes in, the block will discard the serial data, and set a flag to let the program progress to the next section
      if(Serial.available())
      {
        //serial data has come in, so flush the buffer
        while(Serial.available())
        {
          Serial.read();
        } 
        buttonRead =  true;//set the buttonRead flag to true, so that we can exit the while() loop
      }
    }
  }


   Serial.println(" ");
   Serial.println(" ");
   Serial.println(" ");
   Serial.println(" ");
   Serial.println("IR Code Block: ");
   Serial.println(" ");
   Serial.println(" ");
   Serial.println(" ");
   Serial.println(" ");
 
  switch (protocol) {
    case 0:
      Serial.println(F("const unsigned long MY_PROTOCOL = UNKNOWN;"));
      break;
    case 1:
      Serial.println(F("const unsigned long MY_PROTOCOL = NEC;"));
      break;
    case 2:
      Serial.println(F("const unsigned long MY_PROTOCOL = SONY;"));
      break;
    case 3:
      Serial.println(F("const unsigned long MY_PROTOCOL = RC5;"));
      break;
    case 4:
      Serial.println(F("const unsigned long MY_PROTOCOL = RC6;"));
      break;
    case 5:
      Serial.println(F("const unsigned long MY_PROTOCOL = PANASONIC_OLD;"));
      break;
    case 6:
      Serial.println(F("const unsigned long MY_PROTOCOL = JVC;"));
      break;
    case 7:
      Serial.println(F("const unsigned long MY_PROTOCOL = NECX;"));
      break;
    
  }

   for(int i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
    Serial.print("const unsigned long ");
    Serial.print(buttonNames[i]);
    Serial.print(" = 0x");
    Serial.print(ir_data[i], HEX);
    Serial.println(";");
  }
 
} 
 
void loop() 
{ 
  
  


  
  
}

