#pragma once

class Ultrasonic {
public:
  Ultrasonic(int trigPin, int echoPin, float maxDistance);

  float readDistance();
  float readLevel(float distance);
  float smooth(float level);

private:
  int trig;
  int echo;
  float maxDist;

  float prevLevel;
};
