#define BLINK_LED 3
#define TRIGGER_LED 4
#define BUTTON_PIN 5

/**
 * Einmaliges Setup, Pin-Mode konfigurieren.
 */
void setup() {
    pinMode(BLINK_LED, OUTPUT);
    pinMode(TRIGGER_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

// Kontroll-Variablen für blinkende LED
bool blinkLightIsOn = false;
unsigned long lastBlinkLightChange = millis();

// Kontroll-Variablen für Button-gesteuerte LED
bool triggerLightIsOn = false;
unsigned long lastTriggerLightChange = millis();

/**
 * Schaltet Button-gesteuerte LED ein und speichert Zeitpunkt.
 */
void turnLightOn() {
    triggerLightIsOn = true;
    digitalWrite(TRIGGER_LED, HIGH);
    lastTriggerLightChange = millis();
}

/**
 * Schaltet Button-gesteuerte LED aus.
 */
void turnLightOff() {
    digitalWrite(TRIGGER_LED, LOW);
    triggerLightIsOn = false;
}

/**
 * Automatisch wiederholte Loop-Funktion.
 * Eine LED alle 500ms blinken lassen und falls Button gedrückt,
 * zweite LED einschalten, dann nach 1s wieder abschalten.
 */
void loop() {
    unsigned long now = millis();

    // Alle 500ms: Zustand der blinkenden LED umkehren
    if (now - lastBlinkLightChange > 500) {
        digitalWrite(BLINK_LED, blinkLightIsOn ? LOW : HIGH);
        blinkLightIsOn = !blinkLightIsOn;
        lastBlinkLightChange = now;
    }

    // Falls Button-gesteuertes Licht aus und Button gedrückt: anschalten
    if (!triggerLightIsOn && digitalRead(BUTTON_PIN) == HIGH) turnLightOn();
    // Falls Button-gesteuerte LED an und eingeschaltet vor min. 1s: abschalten
    if (now - lastTriggerLightChange > 5000 && triggerLightIsOn) turnLightOff();
}