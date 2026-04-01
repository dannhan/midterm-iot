#include <Arduino.h>

#define TRIG 5
#define ECHO 18

void setup() {
    Serial.begin(115200);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

float readDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    float distance = duration * 0.034 / 2;

    return distance;
}

void loop() {
    float d = readDistance();
    Serial.println(d);
    delay(1000);
}
