#pragma once

class Ultrasonic {
public:
  Ultrasonic(int trigPin, int echoPin, float maxDistance);

  float readDistance();
  float readLevel();
  float smooth(float current);

private:
  int trig;
  int echo;
  float maxDist;

  float prevLevel;
};
