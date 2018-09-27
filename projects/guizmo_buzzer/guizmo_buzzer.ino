/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C6, NOTE_E6, NOTE_D6, NOTE_E6, NOTE_G6, NOTE_F6, NOTE_G6, NOTE_F6, NOTE_G6, NOTE_E6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  400, 800, 400, 400, 1200, 1200, 800, 800, 800, 1200
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 10; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
