// Definiert die Pins, an denen LEDs etc. angeschlossen sind
#include "src/pins.h"
// Klasse zur Verwendung des Ultraschall-Sensors
#include "src/distanceController/DistanceController.h"
// Klasse zur Steuerung von Ampeln
#include "src/trafficLight/TrafficLight.h"

// Ampeln instanziieren
TrafficLight mainStreet(GREEN_MAIN, YELLOW_MAIN, RED_MAIN);
TrafficLight sideStreet(GREEN_SIDE, YELLOW_SIDE, RED_SIDE);

// Abstandssensor, der Verkehr auf Nebenstraße überwacht, instanziieren
DistanceController sideStreetTrigger(TRIGGER_PIN, ECHO_PIN);

// Zeit, die Hauptstraße mindestens hat, bis Nebenstraße das nächste Mal Grün
int minimumMainStreetTime = 5000;

bool trafficQueued = false;
unsigned long previousGreenPhase = millis();

/**
 * Kontrolliert Verkehr auf Nebenstraße: leitet Grünphase ein,
 * falls Autos warten & Hauptstraße schon lange genug Grün hatte
 */
void controlTrafficOnSideStreet() {
    unsigned long now = millis();

    // Kein wartendes Auto / Hauptstraße noch nicht lang genug Grün: Abbrechen
    if (!trafficQueued || now - previousGreenPhase < minimumMainStreetTime) {
        return;
    }

    // Grünphase: Haupstraße auf Rot, danach hat Nebenstraße Grün für 3.5s
    mainStreet.setRed();
    delay(900);
    sideStreet.setGreen();

    delay(3500);

    sideStreet.setRed();
    delay(900);
    mainStreet.setGreen();

    // Zeitpunkt letzter Grünphase und Queue-Status aktualisieren
    trafficQueued = false;
    previousGreenPhase = millis();
}

/**
 * Einmaliges Setup: Ampeln der Hauptstraße auf Grün, der Nebenstraße auf Rot
 */
void setup() {
    mainStreet.setGreen();
    sideStreet.setRed();
}

/**
 * Alle 150ms prüfen, ob Auto in Nebenstraße - falls ja,
 * Ampel der Nebenstraße eine Zeit lang auf Grün stellen
 */
void loop() {
    long distanceToNextCar = sideStreetTrigger.getCurrentDistance();

    // Fahrzeug näher als 20cm: bei nächster Gelegenheit Grünphase auslösen
    if (distanceToNextCar < 20) {
        trafficQueued = true;
    }

    controlTrafficOnSideStreet();
    delay(100);
}
