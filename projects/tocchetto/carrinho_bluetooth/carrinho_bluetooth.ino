// Basic Bluetooth sketch HC-05_03_AT_MODE_Controlled
// Connect the HC-05 module and communicate using the serial monitor
//
// The HC-05 defaults to communication mode when first powered on.
// The default baud rate for communication mode is 9600. Your module may have a different speed.
//
// Pins
// D2 (RX) to HC-05 TX
// D3 (TX) to voltage divider and then HC-05 RX
// HC-05 vcc to 5v
// HC-05 GND to common GND
//
 
#include <SoftwareSerial.h>
// #include <Ultrasonic.h>

int bluetoothTx = 3;
int bluetoothRx = 2;
const int motorA = 5; //velocidade motor A - de 0 a 255
const int motorB = 6; //velocidade motor B - de 0 a 255
const int dirA = 7; //direcao do motor A - HIGH ou LOW
const int dirB = 8; //direcao do motor B - HIGH ou LOW
const int pinfrontLights = 9;    //Pin that activates the Front lights.
const int pinbackLights = 10;    //Pin that activates the Back lights.
//const int pinUltrasonicTrigger = 11;
//const int pinUltrasonicEcho = 12;
const int pinHorn = 13;

SoftwareSerial BTserial(bluetoothRx, bluetoothTx); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
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
    // HC-05 default serial speed for communication mode is 9600
    BTserial.begin(9600); 
     
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
 
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        char command = BTserial.read(); //Recebe caracter via Bluetooth

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

