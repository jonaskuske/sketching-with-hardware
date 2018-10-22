#define SENSOR_MIN 0
#define SENSOR_MAX 1023
#define PHOTO_RESISTOR_PIN A0
#define LED_PIN 12

int photoResistorValue = 0;

bool isLightOn = false;
unsigned long previousTime = millis();
void blink() {
    unsigned long now = millis();

    if (now - previousTime > 400) {
        if (isLightOn) {
            digitalWrite(LED_PIN, LOW);
        } else {
            digitalWrite(LED_PIN, HIGH);
        }
        isLightOn = !isLightOn;
        Serial.print("Licht ist an: ");
        Serial.println(isLightOn);
        previousTime = millis();
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // Get current voltage/value on potentiometer
    delay(50);  // Short delay to ensure accurate reading
    photoResistorValue = analogRead(PHOTO_RESISTOR_PIN);

    Serial.print("Photoresistor: ");
    Serial.println(photoResistorValue);

    int range = map(photoResistorValue, SENSOR_MIN, SENSOR_MAX, 0, 2 + 1);

    Serial.print("");
    Serial.print("Range: ");
    Serial.println(range);

    switch (range) {
        case 0:
            digitalWrite(LED_PIN, HIGH);
            break;
        case 1:
            blink();
            break;
        case 2:
            digitalWrite(LED_PIN, LOW);
            break;
    }
}