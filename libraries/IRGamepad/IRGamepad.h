#ifndef IR_GAMEPAD
#define IR_GAMEPAD

//Create a decoder that handles the hash decoding which will return a 32 bit hash.
#include <IRLibDecodeBase.h>
#include <IRLib_HashRaw.h>  //Must be last protocol
#include <IRLibCombo.h>     // After all protocols, include this
#include <IRLibRecv.h>  // Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop

#include <Arduino.h>

struct GamepadButtons
{
  bool UP;
  bool DOWN;
  bool LEFT;
  bool RIGHT;
  bool START;
  bool SELECT;
  bool B;
  bool TB;
  bool A;
  bool TA;
};

class IR_Gamepad
{
  public:
    IR_Gamepad( int pinID, bool modeB = false );
    void enable();
    bool update_button_states();

    bool button_press_up() { return _buttonStates.UP; }
    bool button_press_down() { return _buttonStates.DOWN; }
    bool button_press_left() { return _buttonStates.LEFT; }
    bool button_press_right() { return _buttonStates.RIGHT; }

    bool button_press_up_left() { return _buttonStates.UP | _buttonStates.LEFT; }
    bool button_press_up_right() { return _buttonStates.UP | _buttonStates.RIGHT; }
    bool button_press_down_left() { return _buttonStates.DOWN | _buttonStates.LEFT; }
    bool button_press_down_right() { return _buttonStates.DOWN | _buttonStates.RIGHT; }

    bool button_press_b() { return _buttonStates.B; }
    bool button_press_tb() { return _buttonStates.TB; }
    bool button_press_btb() { return _buttonStates.B | _buttonStates.TB; }
    bool button_press_a() { return _buttonStates.A; }
    bool button_press_ta() { return _buttonStates.TA; }
    bool button_press_ata() { return _buttonStates.A | _buttonStates.TA; }

    bool button_press_start() { return _buttonStates.START; }
    bool button_press_select() { return _buttonStates.SELECT; }

    unsigned long getCurrentHash();

  private:
    enum CODES_MODE_A
    {
      UP_BUTTON = 0xA7C63817,
      DOWN_BUTTON = 0xE75B5507,
      LEFT_BUTTON = 0xBDC79D57,
      RIGHT_BUTTON = 0xA20D9947,
      SELECT_BUTTON = 0xDE1CA6D7,
      START_BUTTON = 0x84E0D4C7,

      B_BUTTON = 0x44E9D887,
      TB_BUTTON = 0x67D1EE32,
      A_BUTTON = 0xA1CA418B,
      TA_BUTTON = 0x15CC8C46,

      BTB_BUTTON = 0xD3E26ADE, //Buttons B and TB
      ATA_BUTTON = 0x9280089E, //Buttons A and TA

      UPLEFT_BUTTON = 0x20BE5CEB, //Buttons UP and LEFT
      UPRIGHT_BUTTON = 0x50458DB,
      DOWNLEFT_BUTTON = 0x605379DB,
      DOWNRIGHT_BUTTON = 0x449975CB //Buttons DOWN and RIGHT
    };
    enum CODES_MODE_B
    {
      UP_BUTTONB = 0xCC5B8917,
      DOWN_BUTTONB = 0xBF0A607,
      LEFT_BUTTONB = 0xE25CEE57,
      RIGHT_BUTTONB = 0xC6A2EA47,
      SELECT_BUTTONB = 0x2B1F7D7,
      START_BUTTONB = 0xA97625C7,

      B_BUTTONB = 0x697F2987,
      TB_BUTTONB = 0x8C673F32,
      A_BUTTONB = 0xC65F928B,
      TA_BUTTONB = 0x3A61DD46,

      BTB_BUTTONB = 0xF877BBDE, //Buttons B and TB
      ATA_BUTTONB = 0xB715599E, //Buttons A and TA

      UPLEFT_BUTTONB = 0x4553ADEB, //Buttons UP and LEFT
      UPRIGHT_BUTTONB = 0x2999A9DB,
      DOWNLEFT_BUTTONB = 0x84E8CADB,
      DOWNRIGHT_BUTTONB = 0x692EC6CB //Buttons DOWN and RIGHT
    };
  protected:
    int _pinID;
    IRrecv * _IRrecv;
    IRdecode _IRdecoder;
    unsigned long _lastHash;
    bool _contollerModeB;
    GamepadButtons _buttonStates;
};

#endif //--IR_GAMEPAD
