// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
RH_ASK driver;
void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}
void loop()
{  
  /*if (Serial.available() > 0)
  {
    char data[40];
    int numero = Serial.readBytesUntil(13,data,40);
    data[numero] = 0;
    Serial.print("Enviado : ");
    Serial.print(data);
    Serial.print(" - Caracteres : ");
    Serial.println(strlen(data));
    //Envia a mensagem para a rotina que
    //transmite os dados via RF
    send(data);
    delay(200);
  } else {*/
    char *message = "hello";
    send(message);    
  //}
  delay(200);
} 
 
void send (char *message)
{
    driver.send((uint8_t *)message, strlen(message));
    driver.waitPacketSent();
}

