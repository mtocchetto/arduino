#include "Button.h"

Button::Button(int inputPin) {
  m_inputPin = inputPin;
}
 
void Button::begin() {
  pinMode(m_inputPin, INPUT_PULLUP);
}
 
boolean Button::isPressed() {
  return !digitalRead(m_inputPin); // LOW significa que o botao esta sendo pressionado
};