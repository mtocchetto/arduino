#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
  public:
    Button(int inputPin);
    void begin();
    boolean isPressed();
  private:
    int m_inputPin;
};

#endif