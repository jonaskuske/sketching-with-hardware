int lights[] = {7, 8, 9, 10, 11};

int numLights = sizeof(lights) / sizeof(lights[0]);
int currentLight = lights[0];

void setup() {
  // Set all connected pins to Output
  for (int i = 0; i < numLights; i++) pinMode(lights[i], OUTPUT);
}

void loop() {
  for (int i = 0; i < numLights; i++) {
    // Turn off prev light
    digitalWrite(currentLight, LOW);
    // Set next light and turn on
    currentLight = lights[i];
    digitalWrite(currentLight, HIGH);

    delay(100);
  }
}
