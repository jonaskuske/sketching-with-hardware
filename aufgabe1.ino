// An dieser Stelle koennen Variablen deklariert und initialisiert werden.

/* setup Funktion wird beim Programmstart einmalig ausgefuehrt */
void setup() {
    pinMode(9, OUTPUT);  // An Pin 9 ist eine rote LED angeschlossen
    pinMode(8, OUTPUT);  // An Pin 8 ist eine orange LED angeschlossen
    pinMode(7, OUTPUT);  // An Pin 7 ist eine gruene LED angeschlossen
}

/* loop Funktion wird wiederholt solange das Board mit Strom versorgt wird */
void loop() {
    digitalWrite(9, HIGH);  // Rote LED an
    delay(5000);            // Warte 5 Sekunden

    digitalWrite(8, HIGH);  // Orange LED an
    delay(3000);            // Warte 3 Sekunden

    digitalWrite(9, LOW);  // Rote LED aus
    digitalWrite(8, LOW);  // Orange LED aus

    digitalWrite(7, HIGH);  // Grune LED an
    delay(5000);            // Warte 5 Sekunden

    digitalWrite(8, HIGH);  // Orange LED an
    delay(3000);            // Warte 3 Sekunden

    digitalWrite(8, LOW);  // Orange LED aus
    digitalWrite(7, LOW);  // Grune LED aus
}  // und noch einmal