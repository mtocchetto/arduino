//Include the SoftwareSerial library
#include "SoftwareSerial.h"
#include "pitches.h"

#define melodyPin 8
#define NO_SOUND 0 // make the rests in music

//Create a new software  serial
SoftwareSerial bluetooth(2, 3); // TX, RX (Bluetooth)
  
const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  //Initialize the software serial
  bluetooth.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (bluetooth.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = bluetooth.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
      bluetooth.println("LED: ON");
      tone(8, NOTE_C4, 1000);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
      bluetooth.println("LED: OFF");
    }

    if (incomingByte == 'B') {
      bluetooth.println("Banjo Time!!");
      // tone(8, NOTE_C4, 1000);
      //play_jeopardyMelody();
      play_james_bond();
    }
  }
}

void play_james_bond() {

  //* 8-ohm speaker on digital pin 8

  //array of notes
  int melody[] = {
  /*NOTE_G4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
  NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,*/
  
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_DS5,NOTE_D5,NOTE_B4,NOTE_A4,NOTE_B4,
  NOTE_E4,NOTE_G4,NOTE_DS5,NOTE_D5,NOTE_G4,NOTE_B4,
  NOTE_B4,NOTE_FS5,NOTE_F5,NOTE_B4,NOTE_D5,NOTE_AS5,
  NOTE_A5,NOTE_F5,NOTE_A5,NOTE_DS6,NOTE_D6,NO_SOUND
  };
  
  
  // note duration: 1 = whole note, 2 = half note, 4 = quarter note, 8 = eighth note, etc.
  int noteDurations[] = {
  /*8,8,2,8,8,2,16,8,16,8,8,
  2,4,2,4,2,4,2,4,2,4,2,4,2,4,2,4,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,*/
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,2,8,8,1,
  8,4,8,4,8,8,
  8,8,4,8,4,8,
  4,8,4,8,3
  };
  
  int pace = 1450; // change pace of music("speedy")

  for (int Note = 0; Note <54; Note++) {//counter of Notes (54 limit the array)
    int duration = pace/noteDurations[Note];//Adjust duration with the pace of music
    tone(melodyPin, melody[Note],duration); //Play note

    // to distinguish the notes, set a minimum time between them.
    delay(duration*1.2);
  }
}

void play_jeopardyMelody(){
  // notes in the Jeopardy melody:
    int jeopardy[] = {
    NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
    NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4,
    NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_CS4,
    NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
    NOTE_F4, NOTE_D4, NOTE_C4, NOTE_AS3,
    NOTE_A3, NOTE_G3, NOTE_F3};
  
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int jeopardyDurations[] = {
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4,
    3, 8, 8, 8, 8, 8,
    4, 4, 4, 4, 4, 4, 2,
    3, 8, 4, 4,
    4, 4, 4 };

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(jeopardyDurations)/2); thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int jeopardyDuration = 1000/jeopardyDurations[thisNote];
    tone(8, jeopardy[thisNote], jeopardyDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = jeopardyDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

