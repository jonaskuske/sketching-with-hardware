> The basic lesson, a simple traffic light loop.

```cpp
#define RED_LED 2
#define YELLOW_LED 4
#define GREEN_LED 6

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
}

void loop() {
    digitalWrite(RED_LED, HIGH);
    delay(1500);
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    delay(1500);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(1500);
    digitalWrite(GREEN_LED, LOW);
}
```
