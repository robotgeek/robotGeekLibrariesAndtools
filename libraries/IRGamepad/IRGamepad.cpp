#include "IRGamepad.h"

IR_Gamepad::IR_Gamepad( int pinID, bool modeB = false )
{
  _pinID = pinID;
  _IRrecv = new IRrecv( _pinID );
  
  _contollerModeB = modeB;
}
void IR_Gamepad::enable( )
{
  _IRrecv->enableIRIn(); // Start the receiver
}

bool IR_Gamepad::update_button_states()
{
  //Clear old button states
  memset( &_buttonStates, 0, sizeof( _buttonStates ) );
  
  //Process IR data
  getCurrentHash();
  
  //If we are in ModeA process the IR hash
  if ( !_contollerModeB )
  {
    switch ( _lastHash ) 
    {
      case 0:
        return false;
      break;
      case UP_BUTTON:
        _buttonStates.UP = true;
      break;
      case DOWN_BUTTON:
        _buttonStates.DOWN = true;
      break;
      case LEFT_BUTTON:
        _buttonStates.LEFT = true;
      break;
      case RIGHT_BUTTON:
        _buttonStates.RIGHT = true;
      break;
      case START_BUTTON:
        _buttonStates.START = true;
      break;
      case SELECT_BUTTON:
        _buttonStates.SELECT = true;
      break;
      case B_BUTTON:
        _buttonStates.B = true;
      break;
      case TB_BUTTON:
        _buttonStates.TB = true;
      break;
      case A_BUTTON:
        _buttonStates.A = true;
      break;
      case TA_BUTTON:
        _buttonStates.TA = true;
      break;
      case UPLEFT_BUTTON:
        _buttonStates.UP = true;
        _buttonStates.LEFT = true;
      break;
      case UPRIGHT_BUTTON:
        _buttonStates.UP = true;
        _buttonStates.RIGHT = true;
      break;
      case DOWNLEFT_BUTTON:
        _buttonStates.DOWN = true;
        _buttonStates.LEFT = true;
      break;
      case DOWNRIGHT_BUTTON:
        _buttonStates.DOWN = true;
        _buttonStates.RIGHT = true;
      break;
      case BTB_BUTTON:
        _buttonStates.B = true;
        _buttonStates.TB = true;
      break;
      case ATA_BUTTON:
        _buttonStates.A = true;
        _buttonStates.TA = true;
      break;
      default:
        //Serial.print( "Unknown button hash: " );
        //Serial.println(_lastHash, HEX);
        return false;
      break;
    }
  }
  else //Controller expected to be in modeB
  {
    Serial.println( "ModeB" );
    switch ( _lastHash ) 
    {
      case UP_BUTTONB:
        _buttonStates.UP = true;
      break;
      case DOWN_BUTTONB:
        _buttonStates.DOWN = true;
      break;
      case LEFT_BUTTONB:
        _buttonStates.LEFT = true;
      break;
      case RIGHT_BUTTONB:
        _buttonStates.RIGHT = true;
      break;
      case START_BUTTONB:
        _buttonStates.START = true;
      break;
      case SELECT_BUTTONB:
        _buttonStates.SELECT = true;
      break;
      case B_BUTTONB:
        _buttonStates.B = true;
      break;
      case TB_BUTTONB:
        _buttonStates.TB = true;
      break;
      case A_BUTTONB:
        _buttonStates.A = true;
      break;
      case TA_BUTTONB:
        _buttonStates.TA = true;
      break;
      case UPLEFT_BUTTONB:
        _buttonStates.UP = true;
        _buttonStates.LEFT = true;
      break;
      case UPRIGHT_BUTTONB:
        _buttonStates.UP = true;
        _buttonStates.RIGHT = true;
      break;
      case DOWNLEFT_BUTTONB:
        _buttonStates.DOWN = true;
        _buttonStates.LEFT = true;
      break;
      case DOWNRIGHT_BUTTONB:
        _buttonStates.DOWN = true;
        _buttonStates.RIGHT = true;
      break;
      case BTB_BUTTONB:
        _buttonStates.B = true;
        _buttonStates.TB = true;
      break;
      case ATA_BUTTONB:
        _buttonStates.A = true;
        _buttonStates.TA = true;
      break;
      default:
        //Serial.print( "Unknown button hash: " );
        //Serial.println(_lastHash, HEX);
        return false;
      break;
    }
  }
  
  return true;
}

unsigned long IR_Gamepad::getCurrentHash()
{
  unsigned long current_hash = 0;
  
  if (_IRrecv->GetResults(&_IRhashdecoder))
  {
    _IRhashdecoder.decode();
    current_hash = _IRhashdecoder.hash;
    _IRrecv->resume(); 
  }
  
  _lastHash = current_hash; //Store for later use
  return current_hash;
}

