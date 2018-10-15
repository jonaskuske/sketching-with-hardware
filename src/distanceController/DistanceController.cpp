#include "DistanceController.h"
#include "../pinHelpers/pinHelpers.h"
#include "Arduino.h"

/**
 * Constructor:
 * Zugewiesene Pins speichern und pinMode konfigurieren
 */
DistanceController::DistanceController(int triggerPin, int echoPin)
    : _triggerPin(triggerPin), _echoPin(echoPin) {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

/**
 * Misst den Abstand zum Sensor in Zentimetern
 * vgl. https://funduino.de/nr-10-entfernung-messen
 */
long DistanceController::getCurrentDistance() {
    _sendPulse();
    long timeUntilEcho = pulseIn(_echoPin, HIGH);
    // Distanz:
    // Zeit bis zum Echo / 2 (da Hin- und Rückweg) * Schallgeschwindigkeit
    long distanceInCm = timeUntilEcho / 2 * 0.03432;
    return distanceInCm;
}

/**
 * Sendet einen Schall-Puls aus
 */
void DistanceController::_sendPulse() {
    turnPinOff(_triggerPin);
    delay(5);  // kurze Wartezeit, damit vorherige Echos vorbei sind
    turnPinOn(_triggerPin);
    delay(10);
    turnPinOff(_triggerPin);
}
