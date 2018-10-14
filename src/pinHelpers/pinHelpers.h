#ifndef pinHelpers_h
#define pinHelpers_h

#include "Arduino.h"

// Leere Funktionen, um Recursion am Ende des Parameter Packs zu beenden
void turnPinOn(int pin);
void turnPinOff(int pin);

// Variadisches Template: turnPinOn akzeptiert beliebig viele Argumente
template <typename Head, typename... Tail>
void turnPinOn(Head pin, Tail... rest) {
    // Als erstes übergebenen Pin einschalten, dann Recursion: restliche Argumente
    // in erneuten Funktionsaufruf expanden -> alle übergebenen Pins einschalten
    turnPinOn(pin);
    turnPinOn(rest...);
}

// Variadisches Template: turnPinOff akzeptiert beliebig viele Argumente
template <typename Head, typename... Tail>
void turnPinOff(Head pin, Tail... rest) {
    // Als erstes übergebenen Pin ausschalten, dann Recursion: restliche Argumente
    // in erneuten Funktionsaufruf expanden -> alle übergebenen Pins ausschalten
    turnPinOff(pin);
    turnPinOff(rest...);
}

#endif
