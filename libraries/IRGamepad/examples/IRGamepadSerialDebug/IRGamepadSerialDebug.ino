#include <IRGamepad.h>

#define IR_INPUT_PIN 2
bool useModeB = false; //Set to true if your controller is switched to mode B

IR_Gamepad my_gamepad(IR_INPUT_PIN, useModeB);

void setup()
{
  Serial.begin(38400);
  while(!Serial);
  my_gamepad.enable();
}

void loop()
{
  if ( my_gamepad.update_button_states() )
  {
    if ( my_gamepad.button_press_up() ) Serial.print( "UP" );
    if ( my_gamepad.button_press_down() ) Serial.print( "DOWN" );
    if ( my_gamepad.button_press_left() ) Serial.print( "LEFT" );
    if ( my_gamepad.button_press_right() ) Serial.print( "RIGHT" );

    if ( my_gamepad.button_press_start() ) Serial.print( "START" );
    if ( my_gamepad.button_press_select() ) Serial.print( "SELECT" );

    if ( my_gamepad.button_press_b() ) Serial.print( "B" );
    if ( my_gamepad.button_press_tb() ) Serial.print( "TB" );
    if ( my_gamepad.button_press_a() ) Serial.print( "A" );
    if ( my_gamepad.button_press_ta() ) Serial.print( "TA" );

    Serial.println( " button" );
  }

  delay(20);
}

