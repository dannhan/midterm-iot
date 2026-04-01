#include "lcd_status.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

static LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);

// TODO:
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool LcdStatus::begin() {
  Wire.begin(LCD_SDA_PIN, LCD_SCL_PIN);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  ok = true;
  showSplash("HC-SR04", "LCD OK", 900);
  return ok;
}

void LcdStatus::showSplash(const char *line1, const char *line2,
                           unsigned long ms) {
  if (!ok)
    return;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(ms);
}

static void padLineToCols(int len) {
  for (int i = len; i < LCD_COLS; i++)
    lcd.print(' ');
}

void LcdStatus::showReadings(float distanceCm, float levelCm,
                             float smoothedLevelCm) {
  if (!ok)
    return;

  char line1[17];
  char line2[17];

  // Baris 1: sama makna dengan readDistance() — jarak ke target (cm)
  snprintf(line1, sizeof(line1), "D:%.2fcm", distanceCm);
  if ((int)strlen(line1) > LCD_COLS)
    snprintf(line1, sizeof(line1), "D:%.1fcm", distanceCm);

  // Baris 2: level (readLevel) + smooth(level), 2 desimal
  // seperti Serial; jika terlalu panjang, turunkan presisi
  snprintf(line2, sizeof(line2), "L:%.2f S:%.2f", levelCm, smoothedLevelCm);
  if ((int)strlen(line2) > LCD_COLS)
    snprintf(line2, sizeof(line2), "L:%.1f S:%.1f", levelCm, smoothedLevelCm);
  if ((int)strlen(line2) > LCD_COLS)
    snprintf(line2, sizeof(line2), "L:%.0f S:%.0f", levelCm, smoothedLevelCm);

  lcd.setCursor(0, 0);
  lcd.print(line1);
  padLineToCols((int)strlen(line1));

  lcd.setCursor(0, 1);
  lcd.print(line2);
  padLineToCols((int)strlen(line2));
}
