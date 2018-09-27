// #include <Ultrasonic.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

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

const int motorA = 5; //velocidade motor A - de 0 a 255
const int motorB = 6; //velocidade motor B - de 0 a 255
const int dirA = 7; //direcao do motor A - HIGH ou LOW
const int dirB = 8; //direcao do motor B - HIGH ou LOW
const int pinfrontLights = 9;    //Pin that activates the Front lights.
const int pinbackLights = 10;    //Pin that activates the Back lights.
//const int pinUltrasonicTrigger = 11;
//const int pinUltrasonicEcho = 12;
const int pinHorn = 13;

// Ultrasonic ultrasonic(pinUltrasonicTrigger,pinUltrasonicEcho);

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

void setup() 
{ 
    Serial.begin(9600);
    Serial.println("Starting car system...");

    if (driver.init()) {
        Serial.println("Receiver initialized!");
    } else {
        Serial.println("Receiver init failed");
    }
     
    pinMode(motorA, OUTPUT);
    pinMode(motorB, OUTPUT);
    pinMode(dirA, OUTPUT);
    pinMode(dirB, OUTPUT);

    pinMode(pinfrontLights , OUTPUT);
    pinMode(pinbackLights , OUTPUT);
    pinMode(pinHorn , OUTPUT);    
}
 
void loop()
{
    /*
    long distanceCM = ultrasonic.Ranging(CM);
    if(distanceCM <= 5) {
      tone(pinHorn,1500);
    } else {
      noTone(pinHorn);
    }
    */

    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; // RH_ASK_MAX_MESSAGE_LEN
    uint8_t buflen = RH_ASK_MAX_MESSAGE_LEN; //sizeof(buf);

/*
    delay(200);
    char command = STOPPED;
    Serial.print("Default command: ");
    Serial.println(command);
  */  
    if (driver.recv(buf, &buflen)) // Non-blocking
    {  
        /*Serial.print("Message: ");
        for(int i = 0; i < buflen; i++) {
            Serial.print((char) buf[i]);  
        }
        Serial.println();
        */
        // Padrao do buf: "0000 S" com o caracter de comando na posicao 5
        char command = buf[0];// BTserial.read(); //Recebe caracter via Bluetooth
        Serial.print("Command received: ");
        Serial.println(command);
        execute(command);
    } else {
        //execute('S');
    }

}

void execute(char command) {
    Serial.print("Executing command: ");
    Serial.println(command);
    
    switch(command){
    case FORWARD:
        //Move o carrinho para frente
        M1move(255,0);
        M2move(255,0);
        break;
    case BACK:
        //Move o carrinho para trÃ¡s
        M1move(255,1);
        M2move(255,1);
        break;
    case LEFT:
        //Move o carrinho para esquerda
        M1parar();
        M2move(255,1);
        break;
    case RIGHT:
        //Move o carrinho para direita
        M1move(255,1);
        M2parar();
        break;
    case STOPPED:
        //Para o carrinho
        M1parar();
        M2parar();
        break;
    case FORWARD_RIGHT:
        //Diagonal direita para frente
        M2move(255,0);
        M1move(128,0);        
        break;
    case BACK_RIGHT:
        //Diagonal direita para tras
        M2move(255,1);
        M1move(128,1);            
        break;
    case FORWARD_LEFT:
        //Diagonal esquerda para frente
        M1move(255,0);
        M2move(128,0);
        break;
    case BACK_LEFT:
        //Diagonal esquerda para tras
        M1move(255,1);
        M2move(128,1);
        break;
    case FRONT_LIGHTS_ON:
        digitalWrite(pinfrontLights, HIGH);
        break;
    case FRONT_LIGHTS_OFF:
        digitalWrite(pinfrontLights, LOW);
        break;
    case BACK_LIGHTS_ON:
        digitalWrite(pinbackLights, HIGH);
        break;
    case BACK_LIGHTS_OFF:
        digitalWrite(pinbackLights, LOW);
        break;
    case HORN_ON:
        tone(pinHorn,1500); 
        break;
    case HORN_OFF:
        noTone(pinHorn);
        break;
    case EVERYTHING_OFF:
        digitalWrite(pinfrontLights, LOW);
        digitalWrite(pinbackLights, LOW);
        M1parar();
        M2parar();
        break;
    default:
        break;
    }
}

void M1move(int velocidade, int sentido)
{
    analogWrite(motorA, velocidade);
    digitalWrite(dirA, sentido);
}

void M1parar()
{
    analogWrite(motorA, 0);
}

void M2move(int velocidade, int sentido)
{
    analogWrite(motorB, velocidade);
    digitalWrite(dirB, sentido);
}

void M2parar()
{
    analogWrite(motorB, 0);
}

