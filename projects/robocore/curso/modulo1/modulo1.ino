/***************************************\ 
**    ROBOCORE ARDUINO KIT INICIANTE   ** 
*                                       * 
**              Módulo 1               ** 
\***************************************/  
const int ledPin = 13; //led no pino 13 
const int Botao = 2; //botao no pino 2 
int EstadoBotao = 0; //Variavel para ler o status do pushbutton 

void setup(){  
  pinMode(ledPin, OUTPUT); //Pino do led será saída  
  pinMode(Botao, INPUT); //Pino com botão será entrada 
} 

void loop(){  
  /*
   * Novo estado do botão vai ser igual ao que Arduino ler no pino onde está o botão.
   * Poderá ser ALTO (HIGH) se o botão estiver pressionado, 
   * ou BAIXO (LOW),se o botão estiver solto.
   */  
  EstadoBotao = digitalRead(Botao);   
  if (EstadoBotao == HIGH){     //Se botão estiver pressionado (HIGH)   
    digitalWrite(ledPin, HIGH); // acende o led do pino 13.   
  } else {                      //se não estiver pressionado     
    digitalWrite(ledPin, LOW);  //deixa o led do pino 13 apagado  
  }  
}
