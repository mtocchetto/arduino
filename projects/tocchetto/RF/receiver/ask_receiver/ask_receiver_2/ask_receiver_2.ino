// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

uint16_t speed = 2000;
uint8_t rxPin = 11;
uint8_t txPin = 12;
uint8_t pttPin = 10;
bool pttInverted = false;
RH_ASK driver(speed, rxPin, txPin, pttPin, pttInverted);

void setup()
{
  Serial.begin(9600);	// Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  Serial.print("Receiving... ");
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;

    // Message with a good checksum received, dump it.
    driver.printBuffer("Got:", buf, buflen);

    Serial.print("Received: ");
    for (int i = 0; i < buflen; i++) {
      Serial.print((char)buf[i]);
    }
  }    
  Serial.println("");
}
