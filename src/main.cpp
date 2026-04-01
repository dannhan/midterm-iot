#include <Arduino.h>

#define TRIG 5
#define ECHO 18

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.39701

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
    float distance = duration * SOUND_SPEED / 2;

    return distance;
}

void loop() {
    float d = readDistance();
	Serial.print("Distance (cm): ");
	Serial.println(d);
    delay(1000);
}
