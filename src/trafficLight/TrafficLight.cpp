#include "TrafficLight.h"
#include "../pinHelpers/pinHelpers.h"
#include "Arduino.h"

/**
 * Constructor:
 * speichert die LED-Pins, konfiguriert den pinMode und definiert Grün als aktiv
 */
TrafficLight::TrafficLight(int greenPin, int yellowPin, int redPin) {
    _greenPin = greenPin;
    _yellowPin = yellowPin;
    _redPin = redPin;

    pinMode(_greenPin, OUTPUT);
    pinMode(_yellowPin, OUTPUT);
    pinMode(_redPin, OUTPUT);

    _activePin = greenPin;
}

/**
 * Als aktiv markierte LED der Ampel einschalten
 */
void TrafficLight::turnOn() {
    turnPinOn(_activePin);
    isTurnedOn = true;
}

/**
 * Alle LEDs der Ampel ausschalten
 */
void TrafficLight::turnOff() {
    turnPinOff(_greenPin, _yellowPin, _redPin);
    isTurnedOn = false;
}

/**
 * Steuer-Methode, um die Ampel auf Grün zu schalten.
 * Durchläuft die Rot-Gelb-Phase, falls die Ampel zu Beginn auf Rot steht
 */
void TrafficLight::setGreen() {
    if (isTurnedOn && _activePin == _greenPin) {
        // Ampel ist schon grün, keine Änderung nötig
        return;
    }
    if (isTurnedOn && _activePin == _redPin) {
        // Wechsel von Rot: Rot-Gelb-Phase durchlaufen
        turnPinOn(_yellowPin);
        delay(1100);
        turnPinOff(_redPin, _yellowPin);
    }
    // Ampel auf Grün schalten
    turnPinOn(_greenPin);
    _activePin = _greenPin;
    isTurnedOn = true;
}

/**
 * Steuer-Methode, um die Ampel auf Rot zu schalten.
 * Durchläuft die Gelb-Phase, falls die Ampel zu Beginn auf Grün steht
 */
void TrafficLight::setRed() {
    if (isTurnedOn && _activePin == _redPin) {
        return;
    }
    if (isTurnedOn && _activePin == _greenPin) {
        // Wechsel von Grün: Gelb-Phase durchlaufen
        turnPinOff(_greenPin);
        turnPinOn(_yellowPin);
        delay(1100);
        turnPinOff(_yellowPin);
    }
    // Ampel auf Rot schalten
    turnPinOn(_redPin);
    _activePin = _redPin;
    isTurnedOn = true;
}

void TrafficLight::warningMode(int interval) {
    unsigned long currentTime = millis();

    if (currentTime - _previousTime >= interval) {
        if (isTurnedOn) {
            turnOff();
        } else {
            turnPinOn(_yellowPin);
            isTurnedOn = true;
        }
        _previousTime = currentTime;
    }
}

/**
 * Beginnt bei Grün und durchläuft vollständige Ampel-Sequenz mit vier Phasen
 * [Grün -] Gelb - Rot - Rot-Gelb - Grün
 */
void TrafficLight::runDemoSequence(int greenTime, int redTime) {
    setGreen();
    delay(greenTime);
    setRed();
    delay(redTime);
    setGreen();
}