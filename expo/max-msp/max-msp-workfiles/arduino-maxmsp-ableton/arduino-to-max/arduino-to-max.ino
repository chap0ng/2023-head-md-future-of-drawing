void setup() {
  serial.begin(9600); // Serial com set up

}

void loop() {
  knobValue = analogRead(0); // Read sensor val sent from analog in 0
  Serial.println(knobValue); // Send to MaxMSP
  delay(5);
}
