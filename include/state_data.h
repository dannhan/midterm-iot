#pragma once

struct SensorData {
  float distance;
  float level;
  float smooth;
  float humidity;
  float temperature;
};

struct SystemState {
  float prevLevel;
  unsigned long prevTime;
};
