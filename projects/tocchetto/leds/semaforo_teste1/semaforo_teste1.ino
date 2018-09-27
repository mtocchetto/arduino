int ledRed = 12;
int ledYellow = 11;
int ledGreen = 10;
int delayPeriod = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
}

void loop() {
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, HIGH);

  delay(delayPeriod);
  digitalWrite(ledRed, LOW);

  delay(delayPeriod);
  digitalWrite(ledYellow, LOW);
  
  delay(delayPeriod);
  digitalWrite(ledGreen, LOW);

  delay(delayPeriod);
}
