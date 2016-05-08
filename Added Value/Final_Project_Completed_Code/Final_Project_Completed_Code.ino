#include "pitches.h"


int check = 0;
int beep = 0;
int state = 0;
int in1 = 4;
int in2 = 5;

//***********************Set up Note Sequences************************
int hobbit[] = {NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_E3, NOTE_FS3, NOTE_E3, NOTE_D3, 0, NOTE_FS3, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_CS4, NOTE_A3, NOTE_FS3, NOTE_G3, NOTE_FS3, NOTE_E3};
int noteDurationHob[] = {16, 16, 4, 4, 8, 16, 16, 16, 2, 8, 8, 12, 4, 12, 4, 12, 4, 16, 16, 2};

int fwTone[] = {NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_E3, NOTE_FS3};
int noteDurationFwT[] = {8, 8, 8, 8, 8, 8, 4};
//********************************************************************

unsigned long previousTime = 0;
const long interval = 500;   
 
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(7, OUTPUT);
 
  Serial.begin(9600);
}
 
void loop() {
  
//*************************Check for command**************************
  if(Serial.available() > 0){
    state = Serial.read();
    delay(5);
  }
//********************************************************************
  
  play_command(state);

//*********Beep and Blink LED for reverse without using delay*********

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {

    previousTime = currentTime;

    if (check == 0) {
      check = 1;
    } 
    else {
      check = 0;
    }
  }
  
  if (beep == 1){
    if (check == 1) {
      digitalWrite(7, HIGH);
      tone(6, NOTE_B3);
    } 
    else {
      noTone(6);
      digitalWrite(7, LOW);
    }
  }
  else{
    noTone(6);
    digitalWrite(7, LOW);
  }
  
//********************************************************************
  
}

//****************Instruct puppy based on command sent****************

void play_command(int command){

    switch (command) {
    case 'q': //Go forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      for (int thisNote = 0; thisNote < 7; thisNote++) {
        int noteDuration = 1000 / noteDurationFwT[thisNote];
        tone(6, hobbit[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        digitalWrite(7, HIGH);
        delay(pauseBetweenNotes);
        digitalWrite(7, LOW);
      }
      beep = 0;
      break;
    
    case 'w': //Go in reverse
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      beep = 1;
      break;

    case 'e': //Stop motor
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      beep = 0;
      break;
  
    case 'h': //play beginning of concerning hobbits
      for (int thisNote = 0; thisNote < 20; thisNote++) {
        int noteDuration = 1000 / noteDurationHob[thisNote];
        tone(6, hobbit[thisNote], noteDuration);
        
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
      }
      beep = 0;
      break;
  }
}

