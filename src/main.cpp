#include "dht_sensor.h"
#include "lcd_status.h"
#include "led.h"
#include "rate.h"
#include "state.h"
#include "ultrasonic.h"
#include <Arduino.h>

// Sama seperti main di origin/main: pin & jarak maks (cm)
Ultrasonic ultrasonic(5, 18, 16);
LcdStatus display;

RateCalculator rateCalc;
StateMachine stateMachine;

// Pin LED: hijau, kuning, merah
LedController leds(32, 33, 25);

DHTSensor dht(19); // contoh pin

float prevLevel = 0;
unsigned long prevTime = 0;

void setup() {
  Serial.begin(115200);
  if (!display.begin()) {
    Serial.println(F("LCD init failed (cek I2C addr / kabel)."));
  }

  dht.begin();
  leds.begin();
  prevTime = millis();
}

void loop() {
  float distance = ultrasonic.readDistance();
  float level = ultrasonic.readLevel(distance);
  float smoothLevel = ultrasonic.smooth(level);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;

  float rate = rateCalc.compute(smoothLevel, prevLevel, dt);
  State state = stateMachine.update(smoothLevel, rate, humidity);

  display.showReadings(distance, level, smoothLevel);

  leds.update(state);

  leds.update(state);

  Serial.printf(
      "Level: %.2f | Rate: %.2f | Hum: %.2f | Temp: %.2f | State: %s\n",
      smoothLevel, rate, humidity, temperature, stateToString(state));

  prevLevel = smoothLevel;
  prevTime = now;

  delay(600);
}
