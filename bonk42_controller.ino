#include <MIDI.h>

#include <MIDI.h>
#include "Controller.h"


MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 3;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 4;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 0;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 0;
//************************************************************



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

Button BU1(2, 2, 60, 1, 5 );
Button BU2(4, 2, 61, 1, 5 );
Button BU3(7, 3, 62, 1, 5 ); // this button is in the middle
//Button BU4(5, 0, 63, 1, 5 );
//Button BU5(6, 0, 64, 1, 5 );
//Button BU6(7, 0, 65, 1, 5 );
//Button BU7(8, 1, 64, 1, 5 );
//Button BU8(9, 2, 64, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1, &BU2, &BU3};
//*******************************************************************

//***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
//Button::Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

//Button MBU1(M1, 0, 0, 70, 1, 5);
//Button MBU2(M1, 1, 1, 71, 1, 5);
//Button MBU3(M1, 2, 2, 72, 1, 5);
//Button MBU4(M1, 3, 0, 73, 1, 5);
//Button MBU5(M1, 4, 0, 74, 1, 5);
//Button MBU6(M1, 5, 0, 75, 1, 5);
//Button MBU7(M1, 6, 0, 76, 1, 5);
//Button MBU8(M1, 7, 0, 77, 1, 5);
//Button MBU9(M1, 8, 0, 78, 1, 5);
//Button MBU10(M1, 9, 0, 79, 1, 5);
//Button MBU11(M1, 10, 0, 80, 1, 5);
//Button MBU12(M1, 11, 0, 81, 1, 5);
//Button MBU13(M1, 12, 0, 82, 1, 5);
//Button MBU14(M1, 13, 0, 83, 1, 5);
//Button MBU15(M1, 14, 0, 84, 1, 5);
//Button MBU16(M1, 15, 0, 85, 1, 5);
//*******************************************************************
////Add multiplexed buttons used to array below like this->  Button *MUXBUTTONS[] {&MBU1, &MBU2, &MBU3, &MBU4, &MBU5, &MBU6.....};
Button *MUXBUTTONS[] {};

//*******************************************************************


//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//Pot::Pot(Mux mux, byte muxpin, byte command, byte control, byte channel)
//**Command parameter is for future use**

//Pot MPO1(M2, 0, 0, 1, 1);
//Pot MPO2(M2, 1, 0, 7, 1);
//Pot MPO3(M2, 2, 0, 50, 1);
//Pot MPO4(M2, 3, 0, 55, 2);
//Pot MPO5(M2, 4, 0, 50, 1);
//Pot MPO6(M2, 5, 0, 55, 2);
//Pot MPO7(M2, 6, 0, 50, 1);
//Pot MPO8(M2, 7, 0, 55, 2);
//Pot MPO9(M2, 8, 0, 50, 1);
//Pot MPO10(M2, 9, 0, 55, 2);
//Pot MPO11(M2, 10, 0, 50, 1);
//Pot MPO12(M2, 11, 0, 55, 2);
//Pot MPO13(M2, 12, 0, 50, 1);
//Pot MPO14(M2, 13, 0, 55, 2);
//Pot MPO15(M2, 14, 0, 50, 1);
//Pot MPO16(M2, 15, 0, 55, 2);
//*******************************************************************
//Add multiplexed pots used to array below like this->  Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *MUXPOTS[] {};
//*******************************************************************
//set led pins
 int B1R = 3;
 int B1G = 5;
  int B1B = 6;
 int B2R = 11;
 int B2G = 9;
  int B2B = 10;
   int B3R = 8;
 int B3G = 13;
  int B3B = 12;
  
  byte bank = 1; //set default bank/channel
  
void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  //set all the led pins to outputs
  pinMode(B1R, OUTPUT);
  pinMode(B1G, OUTPUT);
    pinMode(B1B, OUTPUT);
      pinMode(B2R, OUTPUT);
  pinMode(B2G, OUTPUT);
    pinMode(B2B, OUTPUT);
      pinMode(B3R, OUTPUT);
  pinMode(B3G, OUTPUT);
    pinMode(B3B, OUTPUT);
   
  Serial.begin(9600);
}


void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();
}

// This bit loops through the buttons and checks for stuff.. record start stop in here as case 4 (command=4) maybe..
//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      // checks what sort of button it is by looking at the command variable..
      switch (BUTTONS[i]->Bcommand) { 
        case 0: //Note - used if its a keybord type of thingy
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
           switchLed(BUTTONS[i]->Bpin, true, bank);
          break;
        case 1: //CC - when button pressed sends 127 when released sends 0
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          switchLed(BUTTONS[i]->Bpin, true, bank);
          break;
        case 2: //Toggle - this is what the two large buttons are set to on this controller press once for 127 and once for 0...
      switch (bank) { // each button class has a toggle variable for each bank to keep track of things. the following sets the correct toggle state sends midi and turns the correct led on/ off
          case 1:
         if (BUTTONS[i]->Btoggle1 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            BUTTONS[i]->Btoggle1 = 1;
          }
          else if (BUTTONS[i]->Btoggle1 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            BUTTONS[i]->Btoggle1 = 0;
          }
          break;
          case 2:
          if (BUTTONS[i]->Btoggle2 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            BUTTONS[i]->Btoggle2 = 1;
          }          
          else if (BUTTONS[i]->Btoggle2 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            BUTTONS[i]->Btoggle2 = 0;
          }
          break;
          case 3:
          if (BUTTONS[i]->Btoggle3 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            BUTTONS[i]->Btoggle3 = 1;
          }          
          else if (BUTTONS[i]->Btoggle3 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            BUTTONS[i]->Btoggle3 = 0;
          }
          break;
          case 4:
          if (BUTTONS[i]->Btoggle4 == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            BUTTONS[i]->Btoggle4 = 1;
          }          
          else if (BUTTONS[i]->Btoggle4 == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            BUTTONS[i]->Btoggle4 = 0;
          }
          break;
          }
          
          break;
case 3: //Change bank.. this cyles through the banks and checks if any leds should be on you could create a 4th case for a record button so command=4
 switch (BUTTONS[i]->Btoggle){ //btoggle is where i store the current bank only used if the button is command 3 other buttons use the specific bank toggle btoggle1 etc
 case 1: 
 BUTTONS[i]->Btoggle = 2;
        for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {

          if (BUTTONS[i]->Btoggle2 == 1 ){
             switchLed(BUTTONS[i]->Bpin, true, 2);
       }
          if (BUTTONS[i]->Btoggle2 == 0){
              switchLed(BUTTONS[i]->Bpin, false, 2);
            
          }
          bank = 2;
           
        }
        
        switchLed(BUTTONS[i]->Bpin, true, 2); 
        break;
case 2:
BUTTONS[i]->Btoggle = 3;
        for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {

          if (BUTTONS[i]->Btoggle3 == 1 ){
             switchLed(BUTTONS[i]->Bpin, true, 3);
       }
          if (BUTTONS[i]->Btoggle3 == 0){
              switchLed(BUTTONS[i]->Bpin, false, 3);
            
          }
          bank = 3;
           
        }
        switchLed(BUTTONS[i]->Bpin, true, 3); 
        break;
    case 3:
    BUTTONS[i]->Btoggle = 4;
        for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {

          if (BUTTONS[i]->Btoggle4 == 1 ){
             switchLed(BUTTONS[i]->Bpin, true, 4);
       }
          if (BUTTONS[i]->Btoggle4 == 0){
              switchLed(BUTTONS[i]->Bpin, false, 4);
            
          }
          bank = 4;
           
        }
        switchLed(BUTTONS[i]->Bpin, true, 4); 
        break;
    case 4: 
    BUTTONS[i]->Btoggle = 1;
        for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {

          if (BUTTONS[i]->Btoggle1 == 1 ){
             switchLed(BUTTONS[i]->Bpin, true, 1);
       }
          if (BUTTONS[i]->Btoggle1 == 0){
              switchLed(BUTTONS[i]->Bpin, false, 1);
            
          }
          bank = 1;
           
        }
        switchLed(BUTTONS[i]->Bpin, true, 1); 
        break;
}
        
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, bank);
          switchLed(BUTTONS[i]->Bpin, false, bank); 
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, bank);
          switchLed(BUTTONS[i]->Bpin, false, bank); 
          break;
      }
    }
  }
}
//*******************************************************************
//ignore this bit.....
void updateMuxButtons() {

  // Cycle through Mux Button array
  for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {

    MUXBUTTONS[i]->muxUpdate();
    byte message = MUXBUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
           switch (bank) {
          case 1:
         if (MUXBUTTONS[i]->Btoggle1 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            MUXBUTTONS[i]->Btoggle1 = 1;
          }
          else if (MUXBUTTONS[i]->Btoggle1 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            MUXBUTTONS[i]->Btoggle1 = 0;
          }
          break;
          case 2:
          if (MUXBUTTONS[i]->Btoggle2 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            MUXBUTTONS[i]->Btoggle2 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle2 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            MUXBUTTONS[i]->Btoggle2 = 0;
          }
          break;
          case 3:
          if (MUXBUTTONS[i]->Btoggle3 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            MUXBUTTONS[i]->Btoggle3 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle3 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            MUXBUTTONS[i]->Btoggle3 = 0;
          }
          break;
          case 4:
          if (MUXBUTTONS[i]->Btoggle4 == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, bank);
            switchLed(BUTTONS[i]->Bpin, true, bank);
            MUXBUTTONS[i]->Btoggle4 = 1;
          }          
          else if (MUXBUTTONS[i]->Btoggle4 == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, bank);
            switchLed(BUTTONS[i]->Bpin, false, bank);
            MUXBUTTONS[i]->Btoggle4 = 0;
          }
          break;
          }
          
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
//***********************************************************************
// this checks the pots put your add to recording code here..
void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, bank);
  }
}

// ignore below
//***********************************************************************
void updateMuxPots() {
  for (int i = 0; i < NUMBER_MUX_POTS; i = i + 1) {
    MUXPOTS[i]->muxUpdate();
    byte potmessage = MUXPOTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(MUXPOTS[i]->Pcontrol, potmessage, MUXPOTS[i]->Pchannel);
  }
}
//this handles the leds (value=button pin number) i think this could be a class holding all the pins for each led using the button pin number as reference..
void switchLed(byte value, bool state, byte bank){
  switch (bank) {
  case 1: 
      switch (value) {
        case 2:
            if (state == true) {
          analogWrite(B1R, 255); 
          analogWrite(B1G, 0); 
          analogWrite(B1B, 0); 
          }
          else{
          analogWrite(B1R, 0);    
          analogWrite(B1G, 0);
          analogWrite(B1B, 0);
          } 
          break;
        case 4:
           if (state == true) {
          analogWrite(B2R, 255); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 0); 
          }
          else{
          analogWrite(B2R, 0); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 0);    
          } 
        case 7:
        if (state == true) {
          digitalWrite(B3R, HIGH); 
          digitalWrite(B3G, LOW); 
          digitalWrite(B3B, LOW); 
          }
           }
          break;
  case 2: 
           switch (value) {
        case 2:
            if (state == true) {
          analogWrite(B1R, 0); 
          analogWrite(B1G, 255); 
          analogWrite(B1B, 0); 
          }
          else{
          analogWrite(B1R, 0);    
          analogWrite(B1G, 0);
          analogWrite(B1B, 0);
          } 
          break;
        case 4:
           if (state == true) {
          analogWrite(B2R, 0); 
          analogWrite(B2G, 255); 
          analogWrite(B2B, 0); 
          }
          else{
          analogWrite(B2R, 0); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 0);    
          } 
        case 7:
        if (state == true) {
          digitalWrite(B3R, LOW); 
          digitalWrite(B3G, HIGH); 
          digitalWrite(B3B, LOW);  
          }
           }
          break;
  case 3: 
          switch (value) {
        case 2:
            if (state == true) {
          analogWrite(B1R, 0); 
          analogWrite(B1G, 0); 
          analogWrite(B1B, 255); 
          }
          else{
          analogWrite(B1R, 0);    
          analogWrite(B1G, 0);
          analogWrite(B1B, 0);
          } 
          break;
        case 4:
           if (state == true) {
          analogWrite(B2R, 0); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 255); 
          }
          else{
          analogWrite(B2R, 0); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 0);    
          } 
        case 7:
        if (state == true) {
          digitalWrite(B3R, LOW); 
          digitalWrite(B3G, LOW); 
          digitalWrite(B3B, HIGH); 
          }
           }
          break;
 case 4: 
           switch (value) {
        case 2:
            if (state == true) {
          analogWrite(B1R, 255); 
          analogWrite(B1G, 0); 
          analogWrite(B1B, 255); 
          }
          else{
          analogWrite(B1R, 0);    
          analogWrite(B1G, 0);
          analogWrite(B1B, 0);
          } 
          break;
        case 4:
           if (state == true) {
          analogWrite(B2R, 255); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 255); 
          }
          else{
          analogWrite(B2R, 0); 
          analogWrite(B2G, 0); 
          analogWrite(B2B, 0);    
          } 
        case 7:
        if (state == true) {
          digitalWrite(B3R, HIGH); 
          digitalWrite(B3G, LOW); 
          digitalWrite(B3B, HIGH); 
          }
           }
          break;
  }
}
