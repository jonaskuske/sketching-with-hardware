#ifndef TrafficLight_h
#define TrafficLight_h

#include "Arduino.h"

/**
 * Klasse für Ampeln, speichert die den Ampel-Lichtern zugewiesenen LED-Pins
 * und stellt Steuer-Methoden für diese bereit
 */
class TrafficLight {
   public:
    TrafficLight(int greenPin, int yellowPin, int redPin, int defaultPin);
    TrafficLight(int greenPin, int yellowPin, int redPin);
    bool isTurnedOn = false, isGreen = false;
    void turnOn();
    void turnOff();
    void setGreen();
    void setRed();
    void warningMode(int interval = 850);
    void runDemoSequence(int greenTime = 2000, int redTime = 2000);

   private:
    int _greenPin, _yellowPin, _redPin, _activePin;
    unsigned long _previousTime;
};

#endif
