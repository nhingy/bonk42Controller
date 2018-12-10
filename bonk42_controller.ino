#include <MIDI.h>
#include "Controller.h"
#include "Constants.h";

MIDI_CREATE_DEFAULT_INSTANCE();

//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**
Pot PO1(A0, 0, 1, 1);
Pot PO2(A1, 0, 10, 1);
Pot PO3(A2, 0, 22, 1);
Pot PO4(A3, 0, 118, 1);
//Pot PO5(A4, 0, 30, 1);
//Pot PO6(A5, 0, 31, 1);
//*******************************************************************
//Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
Pot *POTS[] {&PO1, &PO2, &PO3, &PO4};
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC 3=Bank Change(my new one!)**
Button BU1(2, 2, 60, 1, 5); //Toggle 1
Button BU2(4, 2, 61, 1, 5); //Toggle 2
Button BU3(7, 3, 62, 1, 5); // Bank
//Button BU4(5, 0, 63, 1, 5 );
//Button BU5(6, 0, 64, 1, 5 );
//Button BU6(7, 0, 65, 1, 5 );
//Button BU7(8, 1, 64, 1, 5 );
//Button BU8(9, 2, 64, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1, &BU2, &BU3};
//*******************************************************************

byte bank = 1; //set default bank/channel
  
void setup() {
//  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(B1Red, OUTPUT);
  pinMode(B1Green, OUTPUT);
  pinMode(B1Blue, OUTPUT);
  pinMode(B2Red, OUTPUT);
  pinMode(B2Green, OUTPUT);
  pinMode(B2Blue, OUTPUT);
  pinMode(B3Red, OUTPUT);
  pinMode(B3Green, OUTPUT);
  pinMode(B3Blue, OUTPUT);

  delay(1000);
   
  for (int i=0; i<NUM_BUTTONS; i++){
    BUTTONS[i]->init();
    BUTTONS[i]->setLedPins(RED, BUTTON_LED_PINS[i][0], NO_PIN, NO_PIN); //Sets Red LED pins for button
    BUTTONS[i]->setLedPins(GREEN, BUTTON_LED_PINS[i][1], NO_PIN, NO_PIN); //Sets Green LED pins for button
    BUTTONS[i]->setLedPins(BLUE, BUTTON_LED_PINS[i][2], NO_PIN, NO_PIN); //Sets Blue LED pins for button
    BUTTONS[i]->setLedPins(PURPLE, BUTTON_LED_PINS[i][0], BUTTON_LED_PINS[i][2], NO_PIN); //Sets Purple LED pins for button
  }  
//debug();
  lightUp();
}

void loop() {
  if (NUM_BUTTONS != 0) updateButtons();
  if (NUM_POTS != 0) updatePots();
}

void debug(){
  for (int i=0; i<NUM_BUTTONS; i++){
    BUTTONS[i]->printState();  
  }
}

void lightUp(){
  for (int i=0; i<NUM_BUTTONS; i++){
    if (BUTTONS[i]->getBankBtnStatus(bank) == ON){
      switchLed(BUTTONS[i], true);
    } else {
      switchLed(BUTTONS[i], false);  
    }  
  }        
}

byte getNextBank(){
  if(bank == NUM_BANKS){
    return 1; 
  } else {
    return (bank+1); 
  }      
}

//--------------------------------------------
void updateButtons() {
  for (int i=0; i<NUM_BUTTONS; i++){
    byte message = BUTTONS[i]->getValue();
    if (message == 0) {
      handleButtonPress(BUTTONS[i]);  
    }
    else if (message == 1) {
      handleButtonNotPressed(BUTTONS[i]);  
    }
  }
}

void updatePots() {
  for (int i = 0; i < NUM_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255){
      MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, bank);
    } 
  }
}

void handleButtonPress(Button* button){
  switch (button->Bcommand){ 
    case NOTE: 
      MIDI.sendNoteOn(button->Bvalue, 127, button->Bchannel);
      switchLed(button, true);
      break;
    case TOGGLE: 
      handleToggleBtnPressed(button);
      break;
    case BANK_CHANGE: 
      handleBankBtnPressed(button);
      break;          
  } 
} 

void handleBankBtnPressed(Button* button){
  byte nextBank = getNextBank();
  bank = nextBank;  
  for (int i=0; i<NUM_BUTTONS; i++){
    if (BUTTONS[i]->getBankBtnStatus(bank) == ON){
      switchLed(BUTTONS[i], true);
    } else {
      switchLed(BUTTONS[i], false);   
    }
  }     
}

void handleToggleBtnPressed(Button* button){
  byte midiVal = MIDI_LOW;
  if (button->getBankBtnStatus(bank) == ON){
    midiVal = MIDI_HIGH;
    button->setBankBtnStatus(bank, OFF);
    switchLed(button, false);
  } else {
    button->setBankBtnStatus(bank, ON);
    switchLed(button, true); 
  }
  MIDI.sendControlChange(button->Bvalue, midiVal, bank); 
}

void handleButtonNotPressed(Button* button){
  switch (button->Bcommand) {
    case 0:
      MIDI.sendNoteOff(button->Bvalue, 0, bank);
      switchLed(button, false); 
      break;
    case 1:
      MIDI.sendControlChange(button->Bvalue, 0, bank);
      switchLed(button, false); 
      break;
  }
}

void switchLed(Button* button, bool switchingOn){
  int activeClrStartIndex = (bank * OUTPUT_PINS_PER_BUTTON - OUTPUT_PINS_PER_BUTTON);
  int activeClrEndIndex = (bank * OUTPUT_PINS_PER_BUTTON-1);
  int pinsSwitched[OUTPUT_PINS_PER_BUTTON] = {NO_PIN,NO_PIN,NO_PIN};
  byte pinsSwitchedOn = 0; 
  int* btnColourArray = button->BcolourPins;
  for (int i=0; i<BTN_LED_ARY_SIZE; i++){ //Loop through all buttons pins
    if (switchingOn && (i >= activeClrStartIndex) && (i<= activeClrEndIndex)){ //Found location of a button led pin for this colour
      if((isRealPin(btnColourArray[i])) && (!pinAlreadySwitched(btnColourArray[i], pinsSwitched))){
        writeLedPin(btnColourArray[i], LED_HIGH);
        pinsSwitched[pinsSwitchedOn] = btnColourArray[i];
        pinsSwitchedOn++;
      }
    } else {
      if((isRealPin(btnColourArray[i])) && (!pinAlreadySwitched(btnColourArray[i], pinsSwitched))){
        writeLedPin(btnColourArray[i], LED_LOW);  
      }    
    }    
  }
}

void writeLedPin(int pin, byte val){
    analogWrite(pin, val);
}

bool pinAlreadySwitched(int val, int switchedList[]){
  for(int i=0; i<OUTPUT_PINS_PER_BUTTON; i++){
    if(val == switchedList[i]){
      return true;  
    }    
  } 
  return false;    
}

bool isRealPin(int pinNumber){
  return pinNumber != NO_PIN;    
}
