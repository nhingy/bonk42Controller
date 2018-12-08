#ifndef Constants_h
#define Constants_h

//CONTROLLER BUTTON TYPES
const byte NOTE = 0; 
const byte TOGGLE = 2;
const byte BANK_CHANGE = 3;

//MISC
const byte BUTTON_PRESS = 1;
const byte MIDI_HIGH = 256;
const byte MIDI_LOW = 0;
const byte ON = 1;
const byte OFF = 0; 
const byte LED_HIGH = 255;
const byte LED_LOW = 0; 

//LED PINS
const int B1Red = 3;
const int B1Green = 5;
const int B1Blue = 6;
const int B2Red = 11;
const int B2Green = 9;
const int B2Blue = 10;
const int B3Red = 8;
const int B3Green = 13;
const byte B3Blue = 12;
const byte BANK_1 = 1;
const byte BANK_2 = 2;
const byte BANK_3 = 3;
const byte BANK_4 = 4;

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------

//---How many potentiometers are connected directly to pins?--
const byte NUM_POTS = 4;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 0;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 0;
//************************************************************

#endif
