#ifndef pinHelpers_h
#define pinHelpers_h

#include "Arduino.h"

void turnPinOn(int p);
void turnPinOff(int p);

template <typename Head, typename... Tail>
void turnPinOn(Head pin, Tail... rest) {
    turnPinOn(pin);
    turnPinOn(rest...);
}

template <typename Head, typename... Tail>
void turnPinOff(Head pin, Tail... rest) {
    turnPinOff(pin);
    turnPinOff(rest...);
}

#endif
