#define GREEN_PIN 9
#define YELLOW_PIN 8
#define RED_PIN 7

/**
 * Verwendeten Modus für die LED-Pins konfigurieren, einmalig ausgeführt
 */
void setup() {
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);
}

/**
 * Schaltet die LED an gegebenen Pins ein
 * Akzeptiert beliebige Anzahl an Argumenten
 */
void turnOn() {}
template <typename Head, typename... Tail>
void turnOn(Head pin, Tail... rest) {
    digitalWrite(pin, HIGH);
    turnOn(rest...);
}
/**
 * Schaltet die LED an gegebenen Pins aus
 * Akzeptiert beliebige Anzahl an Argumenten
 */
void turnOff() {}
template <typename Head, typename... Tail>
void turnOff(Head pin, Tail... rest) {
    digitalWrite(pin, LOW);
    turnOff(rest...);
}

/**
 * Klasse für Ampeln, speichert die den Ampel-Lichtern zugewiesenen LED-Pins
 * und stellt Steuer-Methoden für diese bereit
 */
class TrafficLight {
    int green, yellow, red;

   public:
    TrafficLight(int greenPin, int yellowPin, int redPin) {
        green = greenPin;
        yellow = yellowPin;
        red = redPin;
    }

    /**
     * Durchläuft eine vollständige Ampel-Sequenz mit vier Phasen
     */
   public:
    void runSequence() {
        // Grün-Phase
        turnOn(green);
        delay(1800);

        // Gelb-Phase
        turnOff(green);
        turnOn(yellow);
        delay(800);

        // Rot-Phase
        turnOff(yellow);
        turnOn(red);
        delay(1800);

        // Rot-Gelb-Phase
        turnOn(yellow);
        delay(800);

        // Sequenz beendet
        turnOff(red, yellow);
    }
};

TrafficLight demoAmpel = TrafficLight(GREEN_PIN, YELLOW_PIN, RED_PIN);

/**
 * Ampel-Sequenz durchlaufen, wird automatisch wiederholt
 */
void loop() {
    demoAmpel.runSequence();
}
