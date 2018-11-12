#include "LiquidCrystal.h"                              // Library für LCD-Display
#include "src/distanceController/DistanceController.h"  // Klasse für Ultraschall-Sensor
#include "src/pinHelpers/pinHelpers.h"                  // Helfer-Funktionen für Pins
#include "src/pins.h"                                   // Konfiguration der Pins am Arduino

// Abstandsmesser instanziieren
DistanceController distanceMeter(TRIGGER_PIN, ECHO_PIN);

// Display instanziieren
LiquidCrystal lcdDisplay(RS, EN, D4, D5, D6, D7);

/**
 * Schreibt übergebene Zahl als Abstand (in Centimeter) formatiert auf das LCD-Display
 */
void printDistanceToDisplay(long distance) {
    lcdDisplay.clear();          // Zuvor geschriebenes löschen
    lcdDisplay.print(distance);  // Abstand ausgeben
    lcdDisplay.print("CM");      // Einheit (Centimeter) dazu schreiben
}

/**
 * Einmaliges Setup:
 * Pin-Mode konfigurieren und LCD-Library starten
 */
void setup() {
    pinMode(LED_PIN, OUTPUT);
    lcdDisplay.begin(16, 2);
}

/**
 * Loop:
 * Abstand messen, bei gültigem Wert Abstand ausgeben und je nach Abstand Licht ein/ausschalten
 */
void loop() {
    // Aktuellen Abstand messen
    long currentDistance = distanceMeter.getCurrentDistance();

    // Abbrechen und Zurücksetzen, falls gemessener Wert unrealistisch/fehlerhaft ist
    if (currentDistance > 500 || currentDistance < 0) {
        turnPinOff(LED_PIN);  // LED ausschalten
        lcdDisplay.clear();   // Display zurücksetzen
        return;               // Abbrechen
    }

    // Gemessenen Abstand auf Display anzeigen
    printDistanceToDisplay(currentDistance);

    // Licht anschalten, falls gemessener Abstand weniger als 10cm ist, ansonsten ausschalten
    currentDistance < 10 ? turnPinOn(LED_PIN) : turnPinOff(LED_PIN);

    delay(10);
}
