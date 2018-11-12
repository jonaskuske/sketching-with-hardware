#define RED_LED 3
#define GREEN_LED 5
#define BLUE_LED 6

// Steuert, in wie großen Schritten die Farbkanäle heller/dunkel geschaltet werden
int step = 1;
// Geschwindigkeit, mit der die Farben angepasst werden
int timeout = 5;

// Speichert, welcher Übergang des Loops gerade aktiv ist (Rot->Grün, Grün->Blau, Blau->Rot)
int transitionFrom = 0;

// Helligkeitswert der einzelnen Farbkanäle speichern
int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

/**
 * Einmaliges Setup: Pin-Mode konfigurieren
 * und Rot auf maximal stellen (Startfarbe des Color Loops)
 */
void setup() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    redBrightness = 255;
}

/**
 * Loop: Helligkeit der einzelnen Farbkanäle verringern oder erhöhen,
 * sodass ein flüssiger Farbwechsel entsteht
 */
void loop() {
    // Wenn Rot volle Helligkeit hat:
    // gleichzeitig Helligkeit von Rot verringern und Helligkeit von Grün erhöhen.
    // Rot->Grün als aktiven Übergang markieren, damit dieser Vorgang solange weiter läuft,
    // bis der rote Kanal ausgeschaltet ist und der grüne Kanal volle Helligkeit erreicht hat
    if (redBrightness == 255 || transitionFrom == RED_LED) {
        transitionFrom = RED_LED;
        redBrightness -= step;
        greenBrightness += step;
    }

    // Grün hat volle Helligkeit erreicht: Grün als aktiven Übergang vermerken
    // -> ab jetzt Grün verringern & Blau erhöhen, bis Blau volle Helligkeit erreicht hat
    if (greenBrightness == 255 || transitionFrom == GREEN_LED) {
        transitionFrom = GREEN_LED;
        greenBrightness -= step;
        blueBrightness += step;
    }

    // Blau hat volle Helligkeit erreicht: Blau als aktiven Übergang vermerken
    // -> ab jetzt Blau verringern & Rot erhöhen, bis Rot volle Helligkeit erreicht hat
    if (blueBrightness == 255 || transitionFrom == BLUE_LED) {
        transitionFrom = BLUE_LED;
        blueBrightness -= step;
        redBrightness += step;
    }

    // Die geänderten Werte am Ende jedes Durchlaufs des Loops auf die Farbkanäle anwenden
    analogWrite(RED_LED, redBrightness);
    analogWrite(GREEN_LED, greenBrightness);
    analogWrite(BLUE_LED, blueBrightness);

    // Delay, damit der Loop nicht zu schnell abläuft
    delay(timeout);
}