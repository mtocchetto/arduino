#include <Button.h>
 
#define BUTTON1_PIN        8
#define BUTTON2_PIN        9
#define BUTTON3_PIN        10
#define BUTTON4_PIN        11
 
Button button1(BUTTON1_PIN);
Button button2(BUTTON2_PIN);
Button button3(BUTTON3_PIN);
Button button4(BUTTON4_PIN);
int message[4]= {0,0,0,0};
 
void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");
 
  button1.begin();
  button2.begin();
  button3.begin();
  button4.begin(); 
 
  // message = {'0','0','0','0'};
}
 
void loop() {
  Serial.print(button1.isPressed() ? "1" : "0");
  Serial.print(button2.isPressed() ? "1" : "0");
  Serial.print(button3.isPressed() ? "1" : "0");
  Serial.print(button4.isPressed() ? "1" : "0");
  Serial.println("");
  delay(20);
  /*
  for(int i = 0; i < 4; i++) {
    Serial.print(message[i]);
  }
  Serial.println("");
  */
}
