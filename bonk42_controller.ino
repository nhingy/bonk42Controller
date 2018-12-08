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
Button BU1(2, 2, 60, 1, 5);
Button BU2(4, 2, 61, 1, 5);
Button BU3(7, 3, 62, 1, 5); // this button is in the middle
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
  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
  //set all the led pins to outputs
  pinMode(B1Red, OUTPUT);
  pinMode(B1Green, OUTPUT);
  pinMode(B1Blue, OUTPUT);
  pinMode(B2Red, OUTPUT);
  pinMode(B2Green, OUTPUT);
  pinMode(B2Blue, OUTPUT);
  pinMode(B3Red, OUTPUT);
  pinMode(B3Green, OUTPUT);
  pinMode(B3Blue, OUTPUT);
   
  for (int i=0; i<NUM_BUTTONS; i++){
    BUTTONS[i]->init();
  }
}


void loop() {
  if (NUM_BUTTONS != 0) updateButtons();
  if (NUM_POTS != 0) updatePots();
}

// This bit loops through the buttons and checks for stuff.. record start stop in here as case 4 (command=4) maybe..
//*****************************************************************
void updateButtons() {

  // Cycle through Button array
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

// this checks the pots put your add to recording code here..
void updatePots() {
  for (int i = 0; i < NUM_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, bank);
  }
}


//*******************************************************************
void handleButtonPress(Button* button){
  // checks what sort of button it is by looking at the command variable..
  switch (button->Bcommand) { 
        case NOTE: 
          MIDI.sendNoteOn(button->Bvalue, 127, button->Bchannel);
          switchLed(button->Bpin, true);
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
  bank = getNextBank(bank);
  for (int i=0; i<NUM_BUTTONS; i++){
    if (BUTTONS[i]->getBankBtnStatus(bank) == ON){
      switchLed(button->Bpin, true);
    } else {
      switchLed(button->Bpin, false);   
    }
  }     
}

void handleToggleBtnPressed(Button* button){
  byte midiVal = MIDI_LOW;
  if (button->getBankBtnStatus(bank) == OFF){
    midiVal = MIDI_HIGH;
    switchLed(button->Bpin, true);
    button->setBankBtnStatus(bank, ON);
  } else {
    switchLed(button->Bpin, false);
    button->setBankBtnStatus(bank, OFF);  
  }
  
  MIDI.sendControlChange(button->Bvalue, midiVal, bank); 
}

void handleButtonNotPressed(Button* button){
  switch (button->Bcommand) {
    case 0:
      MIDI.sendNoteOff(button->Bvalue, 0, bank);
      switchLed(button->Bpin, false); 
      break;
    case 1:
      MIDI.sendControlChange(button->Bvalue, 0, bank);
      switchLed(button->Bpin, false); 
      break;
  }
}

byte getNextBank(byte currentBank){
  if(currentBank == NUM_BANKS){
    return 1; 
  } else {
    return currentBank+1; 
  }      
}

void switchLed(Button* button, bool state){
  
}
