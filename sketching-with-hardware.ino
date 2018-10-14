// Definiert die Pins, an denen LEDs etc. angeschlossen sind
#include "src/pins.h"
// Definiert Tasten der IR Fernbedienung
#include "src/keys.h"
// Klasse zur Verwendung des Ultraschall-Sensors
#include "src/distanceController/DistanceController.h"
// Klasse zur Steuerung von Ampeln
#include "src/trafficLight/TrafficLight.h"
// IR Library: https://github.com/z3t0/Arduino-IRremote
#include "src/libraries/IRremote/IRremote.h"

IRrecv irrecv(IR_PIN);
decode_results results;

// Ampeln instanziieren, für sideStreet den roten Pin als initialPin angeben
TrafficLight mainStreet(GREEN_MAIN, YELLOW_MAIN, RED_MAIN);
TrafficLight sideStreet(GREEN_SIDE, YELLOW_SIDE, RED_SIDE, RED_SIDE);

// Abstandssensor, der Verkehr auf Nebenstraße überwacht, instanziieren
DistanceController sideStreetTrigger(TRIGGER_PIN, ECHO_PIN);

// Kontroll-Variablen
bool isOff = false;
bool isDisabled = false;

void allowTrafficOnSideStreet() {
    // Schon Grün? Abbruch
    if (sideStreet.isGreen) return;

    mainStreet.setRed();
    delay(900);
    sideStreet.setGreen();
}
void allowTrafficOnMainStreet() {
    // Schon Grün? Abbruch
    if (mainStreet.isGreen) return;
    sideStreet.setRed();
    delay(900);
    mainStreet.setGreen();
}

/**
 * Grünphase der Nebenstraße durchlaufen, danach wieder Rot
 */
void runSideStreetGreenPhase() {
    allowTrafficOnSideStreet();
    delay(3500);
    allowTrafficOnMainStreet();
}

/**
 * Liefert true zurück, falls sich ein Auto nahe der Nebenstraßen-Ampel befindet
 */
bool checkForTrafficOnSideStreet() {
    long distanceToNextCar = sideStreetTrigger.getCurrentDistance();
    return distanceToNextCar < 20;
}
unsigned long previousGreenPhase = millis();
/**
 * Kontrolliert Verkehr auf Nebenstraße: leitet Grünphase ein,
 * falls Autos warten & Hauptstraße schon lange genug Grün hatte
 */
void controlTrafficOnSideStreet() {
    unsigned long now = millis();
    bool trafficQueued = checkForTrafficOnSideStreet();

    // Kein wartendes Auto / Hauptstraße noch nicht mindestens 5s Grün: Abbruch
    if (!trafficQueued || now - previousGreenPhase < 5000) {
        return;
    }

    // Grün-Phase auslösen
    runSideStreetGreenPhase();
    // Zeitpunkt letzter Grünphase und Queue-Status aktualisieren
    trafficQueued = false;
    previousGreenPhase = millis();
}

void handleIRInput(decode_results input) {
    // Long-Press ignorieren
    if (input.value == 0XFFFFFFFF) return;
    // Ein/Aus-Button: Ampeln ein- oder auschalten
    if (input.value == REMOTE_KEY_OFF) {
        isOff = !isOff;
        if (isOff) {
            mainStreet.turnOff();
            sideStreet.turnOff();
        } else {
            mainStreet.turnOn();
            sideStreet.turnOn();
        }
        return;
    }
    // Falls ausgeschaltet: Abbrechen, auf keine anderen Buttons reagieren
    if (isOff) return;
    // EQ-Button: Ampeln als inaktiv markieren (gelbes Blinken)
    if (input.value == REMOTE_KEY_EQ) {
        isDisabled = !isDisabled;
        isOff = false;
        if (!isDisabled) {
            mainStreet.turnOn();
            sideStreet.turnOn();
        }
    }
    // Falls deaktiviert: Abbrechen, auf keine anderen Buttons reagieren
    if (isDisabled) return;

    // Andere Buttons handlen
    switch (input.value) {
        // Play-Button: eine Grün-Phase durchlaufen (simuliert wartendes Auto)
        case REMOTE_KEY_PLAY:
            runSideStreetGreenPhase();
            break;
        // Vor/Zurück-Buttons: Zwischen Grün auf Haupt- und Nebenstraße wechseln
        case REMOTE_KEY_PREV:
        case REMOTE_KEY_NEXT:
            if (mainStreet.isGreen) {
                allowTrafficOnSideStreet();
            } else {
                allowTrafficOnMainStreet();
            }
            break;
    }
}

/**
 * Einmaliges Setup: IRremote aktivieren
 */
void setup() {
    // Serial.begin(9600);  // Serial Monitor aktivieren

    irrecv.enableIRIn();
    irrecv.blink13(true);
}

/**
 * Alle 50ms prüfen, ob Auto in Nebenstraße - falls ja,
 * Ampel der Nebenstraße eine Zeit lang auf Grün stellen
 */
void loop() {
    // Input der IR Fernbedienung verarbeiten
    if (irrecv.decode(&results)) {
        handleIRInput(results);
        irrecv.resume();
    }

    // Ampeln aus? Abbruch
    if (isOff) return;

    // Ampeln deaktiviert? Warn-Modus (gelbes Blinken)
    if (isDisabled) {
        mainStreet.warningMode();
        sideStreet.warningMode();
        return;
    }

    // Verkehr beobachten und managen
    controlTrafficOnSideStreet();
    delay(50);
}