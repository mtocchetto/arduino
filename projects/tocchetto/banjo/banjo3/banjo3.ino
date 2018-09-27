#include <SD.h>  
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h> 

TMRpcm audio;   // create an object for use in this sketch
int tonePin = 9; // for Uno

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  audio.speakerPin = tonePin; //11 on Mega, 9 on Uno, Nano, etc

  // Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
}

void loop() {
  
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  Serial.println(sensorVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    // digitalWrite(13, LOW);
  } else {
    // digitalWrite(13, HIGH);
    play_banjo();
  }
}

void play_banjo() {
  // https://github.com/TMRh20/TMRpcm/wiki
  audio.setVolume(5); // max 7
  audio.play("banjo1.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
}
