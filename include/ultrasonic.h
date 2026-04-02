#pragma once

void ultrasonicBegin(int trig, int echo);

float readDistance(int trig, int echo);
float computeLevel(float distance, float maxDist);
float smoothLevel(float current, float previous);
