#include <Ultrasonic.h>

const int leftEye = 9;
const int rightEye = 10;
const int pinUltrasonicTrigger = 11;
const int pinUltrasonicEcho = 12;

Ultrasonic ultrasonic(pinUltrasonicTrigger,pinUltrasonicEcho);

void setup() {
    pinMode(leftEye, OUTPUT);
    pinMode(rightEye, OUTPUT);
}

void loop() {
    long distanceCM = ultrasonic.Ranging(CM);
    if(distanceCM <= 30) {
      digitalWrite(leftEye, HIGH);
      digitalWrite(rightEye, HIGH);
    } else {
      digitalWrite(leftEye, LOW);
      digitalWrite(rightEye, LOW);
    }
}
