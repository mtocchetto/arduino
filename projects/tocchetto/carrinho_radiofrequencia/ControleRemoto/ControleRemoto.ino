#include <Button.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char FORWARD = 'F';
const char BACK = 'B';
const char LEFT = 'L';
const char RIGHT = 'R';  
const char STOPPED = 'S';
const char FORWARD_RIGHT = 'I';
const char BACK_RIGHT = 'J';
const char FORWARD_LEFT = 'G';
const char BACK_LEFT = 'H';
const char FRONT_LIGHTS_ON = 'W';
const char FRONT_LIGHTS_OFF = 'w';
const char BACK_LIGHTS_ON = 'U';
const char BACK_LIGHTS_OFF = 'u';
const char EVERYTHING_OFF = 'D';
const char HORN_ON = 'V';
const char HORN_OFF = 'v';

#define BUTTON_FORWARD_PIN    8
#define BUTTON_BACK_PIN       9
#define BUTTON_LEFT_PIN       10
#define BUTTON_RIGHT_PIN      11
 
Button buttonForward(BUTTON_FORWARD_PIN);
Button buttonBack(BUTTON_BACK_PIN);
Button buttonLeft(BUTTON_LEFT_PIN);
Button buttonRight(BUTTON_RIGHT_PIN);

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

uint16_t  speed = 2000;
uint8_t   rxPin = 3;
uint8_t   txPin = 4;
uint8_t   pttPin = 2;
bool  pttInverted = false; 

RH_ASK driver(speed, rxPin, txPin, pttPin, pttInverted);
/*
RH_ASK::RH_ASK  ( uint16_t  speed = 2000,
uint8_t   rxPin = 11,
uint8_t   txPin = 12,
uint8_t   pttPin = 10,
bool  pttInverted = false 
)
*/ 
   
void setup() {  
  Serial.begin(9600);
  Serial.println("Starting program...");
 
  buttonForward.begin();
  buttonBack.begin();
  buttonLeft.begin();
  buttonRight.begin(); 
  
  if (!driver.init())
    Serial.println("init failed");
  // message = {'0','0','0','0'};
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("WALL-E TOCCHETTO");
}
 
void loop() {
  boolean goForward = buttonForward.isPressed();
  boolean goBack = buttonBack.isPressed();
  boolean turnLeft = buttonLeft.isPressed();
  boolean turnRight = buttonRight.isPressed();

  char command = getCommand(goForward, goBack, turnLeft, turnRight);

  char message[16];
  message[0] = goForward ? '1' : '0';
  message[1] = goBack ? '1' : '0';
  message[2] = turnLeft ? '1' : '0';
  message[3] = turnRight ? '1' : '0';
  message[4] = ' ';
  message[5] = command;  
  message[6] = '\0';
  
  lcd.setCursor(0,1);
  lcd.print(message);

  message[0] = command;
  message[1] = '\0';
  send(message);

  delay(20);
}

char getCommand(boolean goForward, boolean goBack, boolean turnLeft, boolean turnRight) {  
  char command = STOPPED;
  if(goForward && !goBack) {
    command = turnLeft ? FORWARD_LEFT : turnRight ? FORWARD_RIGHT : FORWARD;
  } else if (goBack && !goForward) {
    command = turnLeft ? BACK_LEFT : turnRight ? BACK_RIGHT : BACK;    
  } else if(turnLeft && !turnRight) {
    command = LEFT;
  } else if(turnRight && !turnLeft) {
    command = RIGHT;
  }
  return command;
}

char* getLCDMessage(char command) {
  // TODO ver como usar enum para simplificar isso
  char* message;
  switch(command) {
  case 'F':
    message = "FORWARD";
    break;
  case 'B':
    message = "BACK";
    break;
  case 'L':
    message = "LEFT";
    break;
  case 'R':
    message = "RIGHT";
    break;
  case 'S':
    message = "STOPPED";
    break;
  case 'I':
    message = "FORWARD_RIGHT";
    break;
  case 'J': 
    message = "BACK_RIGHT"; 
    break;
   case 'G':
    message = "FORWARD_LEFT";
    break;
  case 'H':
    message = "BACK_LEFT";
    break;
  case 'W':
    message = "FRONT_LIGHTS_ON";
    break;
  case 'w':
    message = "FRONT_LIGHTS_OFF";
    break;
  case 'U':
    message = "BACK_LIGHTS_ON";
    break;
  case 'u':
    message = "BACK_LIGHTS_OFF";
    break;
  case 'D':
    message = "EVERYTHING_OFF";
    break;
  case 'V':
    message = "HORN_ON";
    break;
  case 'v':
    message = "HORN_OFF";
    break;
  default:
    message = "";
  }
  return message;
}

void send(const char* message)
{
    Serial.print("Sending message: ");
    Serial.println(message);
    driver.send((uint8_t *)message, strlen(message));
    driver.waitPacketSent();
}
