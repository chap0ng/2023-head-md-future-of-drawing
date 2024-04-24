int val[6];  // Array for 6 sensors

void setup() {
  Serial.begin(9600);  // Serial com set up
}

void loop() {
  // Read analog in one by one and send to maxMSP
  for (int i = 0; i < 6; i++) {
    val[i] = analogRead(i);
    Serial.print(val[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(50);
}
