#define REMOTE_TYPE MINI_REMOTE_1

#define MINI_REMOTE_1 0001
#define MINI_REMOTE_2 0002
#define SONY_DVD 0003

const unsigned long  REPEATING = 0xFFFFFFFF;

#if REMOTE_TYPE == MINI_REMOTE_1

  // You will have to set these values depending on the protocol
  // and remote codes that you are using. These are from the Adafruit Mini Remote
const unsigned long MY_PROTOCOL = NEC;
const unsigned long RIGHT_BUTTON = 0xFD50AF;
const unsigned long LEFT_BUTTON = 0xFD10EF;
const unsigned long UP_BUTTON = 0xFDA05F;
const unsigned long DOWN_BUTTON = 0xFDB04F;
const unsigned long SELECT_BUTTON = 0xFD906F;
const unsigned long ONE_BUTTON = 0xFD08F7;
const unsigned long TWO_BUTTON = 0xFD8877;
const unsigned long THREE_BUTTON = 0xFD48B7;
const unsigned long FOUR_BUTTON = 0xFD28D7;
const unsigned long FIVE_BUTTON = 0xFDA857;
const unsigned long SIX_BUTTON = 0xFD6897;
const unsigned long SEVEN_BUTTON = 0xFD18E7;
const unsigned long EIGHT_BUTTON = 0xFD9867;
const unsigned long NINE_BUTTON = 0xFD58A7;
const unsigned long ZERO_BUTTON = 0xFD30CF;
const unsigned long SPECIAL_1_BUTTON = 0xFD00FF;
const unsigned long SPECIAL_2_BUTTON = 0xFD40BF;


#elif REMOTE_TYPE == MINI_REMOTE_2

  // You will have to set these values depending on the protocol
  // and remote codes that you are using. These are from my Sony DVD/VCR
const unsigned long MY_PROTOCOL = NEC;
const unsigned long RIGHT_BUTTON = 0xFFC23D;
const unsigned long LEFT_BUTTON = 0xFF22DD;
const unsigned long UP_BUTTON = 0xFF629D;
const unsigned long DOWN_BUTTON = 0xFFA857;
const unsigned long SELECT_BUTTON = 0xFF02FD;
const unsigned long ONE_BUTTON = 0xFF6897;
const unsigned long TWO_BUTTON = 0xFF9867;
const unsigned long THREE_BUTTON = 0xFFB04F;
const unsigned long FOUR_BUTTON = 0xFF30CF;
const unsigned long FIVE_BUTTON = 0xFF18E7;
const unsigned long SIX_BUTTON = 0xFF7A85;
const unsigned long SEVEN_BUTTON = 0xFF10EF;
const unsigned long EIGHT_BUTTON = 0xFF38C7;
const unsigned long NINE_BUTTON = 0xFF5AA5;
const unsigned long ZERO_BUTTON = 0xFF4AB5;
const unsigned long SPECIAL_1_BUTTON = 0xFF42BD;
const unsigned long SPECIAL_2_BUTTON = 0xFF52AD;



#elif REMOTE_TYPE == SONY_DVD

  // You will have to set these values depending on the protocol
  // and remote codes that you are using. These are from my Sony DVD/VCR
const unsigned long MY_PROTOCOL = SONY;
const unsigned long RIGHT_BUTTON = 0x3EB92;
const unsigned long LEFT_BUTTON = 0xDEB92;
const unsigned long UP_BUTTON = 0x9EB92;
const unsigned long DOWN_BUTTON = 0x5EB92;
const unsigned long SELECT_BUTTON = 0xD0B92;
const unsigned long ONE_BUTTON = 0xB92;
const unsigned long TWO_BUTTON = 0x80B92;
const unsigned long THREE_BUTTON = 0x40B92;
const unsigned long FOUR_BUTTON = 0xC0B92;
const unsigned long FIVE_BUTTON = 0x20B92;
const unsigned long SIX_BUTTON = 0xA0B92;
const unsigned long SEVEN_BUTTON = 0x60B92;
const unsigned long EIGHT_BUTTON = 0xE0B92;
const unsigned long NINE_BUTTON = 0x10B92;
const unsigned long ZERO_BUTTON = 0x90B92;
const unsigned long SPECIAL_1_BUTTON = 0xC81;
const unsigned long SPECIAL_2_BUTTON = 0x481;



#endif


