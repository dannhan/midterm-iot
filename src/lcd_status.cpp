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

void lcdShowReadings(float d, float l, float s) {
  char line1[17];
  char line2[17];

  snprintf(line1, sizeof(line1), "D:%.2fcm", d);
  if ((int)strlen(line1) > LCD_COLS)
    snprintf(line1, sizeof(line1), "D:%.1fcm", d);

  snprintf(line2, sizeof(line2), "L:%.2f S:%.2f", l, s);
  if ((int)strlen(line2) > LCD_COLS)
    snprintf(line2, sizeof(line2), "L:%.1f S:%.1f", l, s);
  if ((int)strlen(line2) > LCD_COLS)
    snprintf(line2, sizeof(line2), "L:%.0f S:%.0f", l, s);

  lcd.setCursor(0, 0);
  lcd.print(line1);
  pad(strlen(line1));

  lcd.setCursor(0, 1);
  lcd.print(line2);
  pad(strlen(line2));
}
