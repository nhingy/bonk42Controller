#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

const byte NUM_BANKS = 4;
const int OUTPUT_PINS_PER_BUTTON = 3;
const int NUM_COLOURS = 4;
const byte NUM_BUTTONS = 3;
const byte BANK_CHANGE = 3;

//***********************************************************************
class Mux
{
  public:
    Mux(byte outpin_, byte numPins_, bool analog_);
    byte outpin;
    byte numPins;
    bool analog;
};
//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public: 
    Button(byte pin, byte command, byte value, byte channel, byte debounce);
    Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce);
    byte getValue();
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    byte getBankBtnStatus(byte bank);
    void setBankBtnStatus(byte bank, byte onOff);
    void setLedPins(int colour, int pin1, int pin2, int pin3);
    void printState();
    void init();
    byte Bcommand;
    byte Bvalue;
    byte Bchannel;
    byte Bpin;
    byte BbankBtnStatus[NUM_BANKS];
    int BcolourPins[OUTPUT_PINS_PER_BUTTON*NUM_COLOURS];
    
  private:
    byte _previous;
    byte _current;
    unsigned long _time;
    int _debounce;
    byte _muxpin;
    byte _numMuxPins;
    byte _value;
    byte _command;
    bool _busy;
    byte _status;
    byte _last;
    byte _enablepin;
    byte _pin;
};

//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    Pot(Mux mux, byte muxpin ,byte command, byte control, byte channel);
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    byte getValue();
    byte Pcommand;
    byte Pcontrol;
    byte Pchannel;
    byte Ppin;

  private:
    byte _pin;
    byte _muxpin;
    byte _numMuxPins;
    byte _control;
    int _value;
    int _oldValue;
    bool _changed;
    byte _enablepin;
};


#endif
