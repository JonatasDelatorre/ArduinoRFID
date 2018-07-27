void setup() {
  Serial.begin(9600);

}

void loop() {
    digitalWrite(4, HIGH);
    Serial.println("Led verde ligado");
    delay(2000);
    Serial.println("Led verde desligado");
    digitalWrite(4, LOW);
}
