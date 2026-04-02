#include "lcd_status.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <cstring>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void lcdBegin(int sda, int scl) {
  Wire.begin(sda, scl);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void lcdSplash(const char *l1, const char *l2, unsigned long ms) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);
  delay(ms);
}

static void pad(int len) {
  for (int i = len; i < LCD_COLS; i++)
    lcd.print(' ');
}

static const char *stateLabel(State s) {
  switch (s) {
  case State::SAFE:
    return "SAFE";
  case State::ALERT:
    return "ALERT";
  case State::DANGER:
    return "DANGER";
  }
  return "UNKNOWN";
}

void lcdShowStatus(State state, float level, float rate, float humidity) {
  char line1[17];
  char line2[17];

  // --- LINE 1: STATE ---
  snprintf(line1, sizeof(line1), "%-6s H:%2.0f%%", stateLabel(state), humidity);

  // --- LINE 2: LEVEL + RATE ---
  snprintf(line2, sizeof(line2), "L:%4.1f R:%3.1f", level, rate);

  lcd.setCursor(0, 0);
  lcd.print(line1);
  pad(strlen(line1));

  lcd.setCursor(0, 1);
  lcd.print(line2);
  pad(strlen(line2));
}
