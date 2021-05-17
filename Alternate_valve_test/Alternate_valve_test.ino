

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(5, OUTPUT); pinMode(6, OUTPUT); pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH); digitalWrite(6, LOW);    digitalWrite(7, LOW);
  delay(5000);                   
  digitalWrite(5, LOW); digitalWrite(6, HIGH);   digitalWrite(7, HIGH);
  delay(5000);                      
}
