#define SENSOR_MIN 0
#define SENSOR_MAX 1023
#define PHOTO_RESISTOR_PIN A0
#define LED_PIN 12

// Wert des Photoresistors (Helligkeit)
int photoResistorValue = 0;

// Speichern, ob LED aus oder an & wann LED zuletzt umgeschaltet wurde
bool isLightOn = false;
unsigned long previousTime = millis();

/**
 * Funktion, um LED blinken zu lassen:
 * Alle 400ms LED wahlweise aus oder einschalten,
 * je nach vorherigem Zustand
 */
void blink() {
    unsigned long now = millis();

    // Falls seit letztem Umschalten der LED keine 400ms vergangen: Abbrechen
    if (now - previousTime < 400) return;

    // Licht aktuell an? Ausschalten
    // Ansonsten: Einschalten
    if (isLightOn) {
        digitalWrite(LED_PIN, LOW);
    } else {
        digitalWrite(LED_PIN, HIGH);
    }

    // Zustand des Lichts umschalten
    isLightOn = !isLightOn;
    // Zeitpunkt der letzten Umschaltung aktualisieren
    previousTime = now;
}

/**
 * Einmalige Initialisierung von LED-Pin und seriellem Monitor
 */
void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

/**
 * Ständig die aktuelle Helligkeit prüfen und darauf reagieren
 */
void loop() {
    // Aktuellen Helligkeits-Wert vom Sensor abrufen und speichern
    delay(50);  // Verzögerung, um Messung nicht zu verfälschen
    photoResistorValue = analogRead(PHOTO_RESISTOR_PIN);

    // Helligkeits-Wert ausgeben
    Serial.print("Photoresistor: ");
    Serial.println(photoResistorValue);

    // Helligkeits-Wert in Wert zwischen 0 und 2 umrechnen,
    // je nach dem ob sehr dunkel, mittlerer Wert oder sehr hell
    int brightness = map(photoResistorValue, SENSOR_MIN, SENSOR_MAX, 0, 2 + 1);

    // Sehr dunkel? Licht an
    // Mittlerer Wert? Blinken
    // Sehr hell? Licht aus
    switch (brightness) {
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
