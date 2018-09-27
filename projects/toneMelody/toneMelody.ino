/*
 littleBits Arduino Module
 Based on Arduino toneMelody sketch:
 created 21 Jan 2010 by Tom Igoe
 modified 30 Aug 2011 by Tom Igoe
 http://arduino.cc/en/Tutorial/Tone
 modified for littleBits March 2014 by Matt Richard
 
 _Tone Melody_
 
   What is supposed to happen:
 * Plays the Final Jeopardy theme song using the tone command.
 
   Circuit:
 * LittleBits speaker on digital pin 9 (will not work with buzzer)
 
 This sketch includes the following commands:
 delay(time);                                   time: milliseconds
 noTone();                                      ends all tones. Must use between tone commands
 tone(pin, frequency, duration);                pin: digital pin 9
                                                frequency: the frequency of the tone in hertz
                                                duration: the duration of the tone in milliseconds
 
 Additional Notes:
 This sketch also includes two integer arrays named "jeopardy" and "jeopardyDurations".
 Arrays allow you to store multiple values of the same datatype under one name.
 This functionality combined with a for loop makes it easy to write code that refernces a lot of values.
 
 */

#include "pitches.h"

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
  
void setup() {
  //nothing to do here
}

void loop() {
  // continuously repeat the melody.
  play_jeopardyMelody();
}

void play_jeopardyMelody(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(jeopardyDurations)/2); thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int jeopardyDuration = 1000/jeopardyDurations[thisNote];
    tone(9, jeopardy[thisNote], jeopardyDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = jeopardyDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);
  }
}


