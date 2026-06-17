#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

void drawScreen_1(Adafruit_SSD1306* gfx);
void HOMING_OLED(Adafruit_SSD1306* gfx);
void RAIL_COUNT_OLED(Adafruit_SSD1306* gfx);
void RAIL_DISPLAY_COUNT(Adafruit_SSD1306* gfx, int32_t count);
void CENTERING_OLED(Adafruit_SSD1306* gfx);
void DONE_SETUP_OLED(Adafruit_SSD1306* gfx);
void RAIL_LENGTH_OLED(Adafruit_SSD1306* gfx, float len);

#endif