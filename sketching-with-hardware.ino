#define LED_PIN 9
#define BUTTON_PIN 8

// Kontrollvariablen, um Helligkeit der LED und Abstufung beim Faden zu steuern
int brightness = 0;
int fadeStep = 5;

// active State, entscheidet ob LED blinkt oder ausgefadet wird
bool isActive = false;

/**
 * Modus der LED Pins konfigurieren, einmalig ausgeführt
 */
void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

// Timing-Variablen: speichern wann Button das letzte Mal gedrückt / LED das letzte Mal umgeschaltet
// Lässt sich dann mit aktueller Zeit vergleichen, um zu wissen wie viel Zeit seitdem vergangen ist
unsigned long lastButtonPress = millis();
unsigned long lastLEDUpdate = millis();

/**
 * Loop-Funktion, wird automatisch wiederholt:
 * Erst Button überprüfen und active State entsprechend aktualisieren,
 * dann abhängig von active State wahlweise LED blinken lassen oder ausfaden.
 */
void loop() {
    // Aktuelle Zeit, lässt sich mit Timing-Variablen (siehe oben) vergleichen
    unsigned long now = millis();
    // Ist true oder false, je nachdem ob Button aktuell gedrückt wird oder nicht
    bool buttonIsPressed = digitalRead(BUTTON_PIN) == HIGH;

    // Falls Button gedrückt und min. 800ms seit letztem Auslösen vorbei: active State umschalten
    // (800ms "Cooldown" nötig, um bei gedrückt halten nicht ständig hin und her zu schalten)
    if (buttonIsPressed && now - lastButtonPress > 800) {
        isActive = !isActive;
        // Zeitpunkt des letzen Button-Press aktualisieren: Cooldown startet bei nächstem Loop neu
        lastButtonPress = now;
    }

    if (isActive) {
        // Active? LED blinken lassen
        // Falls 100ms vorbei, seit LED letztes mal ein- bzw. ausgeschaltet, LED wieder umschalten
        if (now - lastLEDUpdate > 100) {
            // Falls Helligkeit größer 0, auf 0 stellen, ansonsten auf maximal: an, aus, an, aus...
            brightness = brightness > 0 ? 0 : 255;
            // LED-Helligkeit aktualisieren
            analogWrite(LED_PIN, brightness);
            // Zeitpunkt des letzen LED-Updates aktualisieren: Blink-Interval beginnt von vorne
            lastLEDUpdate = now;
        }
    } else {
        // Nicht active? LED ausfaden bzw. ausgeschaltet lassen
        // Falls LED noch hell genug um faden zu können, Helligkeit stufenweise verringern
        // Ansonsten ganz ausschalten bzw. ausgeschaltet lassen (brightness = 0)
        if (brightness >= fadeStep) {
            brightness = brightness - fadeStep;
        } else {
            brightness = 0;
        }
        // LED-Helligkeit aktualisieren
        analogWrite(LED_PIN, brightness);
        // Delay für Fade-Effekt
        delay(20);
    }
}