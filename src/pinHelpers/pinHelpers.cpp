#include "pinHelpers.h"
#include "Arduino.h"

/**
 * Leere Funktion, beendet Recursion am Ende des Parameter Packs
 */
void turnPinOn(){};
/**
 * Schaltet gegebene Pin auf ein / HIGH
 * Nimmt dank Variadic-Template in pinHelpers.h beliebige Anzahl an Argumenten
 */
void turnPinOn(int pin) {
    digitalWrite(pin, HIGH);
}

/**
 * Leere Funktion, beendet Recursion am Ende des Parameter Packs
 */
void turnPinOff(){};
/**
 * Schaltet gegebene Pin auf aus / LOW
 * Nimmt dank Variadic-Template in pinHelpers.h beliebige Anzahl an Argumenten
 */
void turnPinOff(int pin) {
    digitalWrite(pin, LOW);
}