#ifndef PinSet_h
#define PinSet_h






const byte MAX_PINS_PER_COLOUR = 3;

public class PinSet
{
  public:
    PinSet();
    byte getColour();
    byte getPin(byte pinNumer);
  private: 
    byte _colour; 
    byte _ledPins[MAX_PINS_PER_COLOUR];
};

#endif
