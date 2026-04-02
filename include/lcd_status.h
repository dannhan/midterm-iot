#pragma once

// LCD 16x2 + I2C. Tampilan selaras dengan ultrasonic.cpp (origin/main):
//   readDistance() -> jarak (cm)
//   readLevel()    -> maxDist - distance, terklaim [0, maxDist]
//   smooth(level)  -> EMA 0.7*prev + 0.3*current

#define LCD_I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_SDA_PIN 21
#define LCD_SCL_PIN 22

class LcdStatus {
public:
  bool begin();
  void showReadings(float distanceCm, float levelCm, float smoothedLevelCm);
  void showSplash(const char *line1, const char *line2,
                  unsigned long ms = 1500);

private:
  bool ok = false;
};
