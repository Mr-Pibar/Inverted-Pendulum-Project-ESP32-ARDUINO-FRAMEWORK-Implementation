    #include <oled.h>
    #include <Wire.h>
    #include <SPI.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>

void drawScreen_1(Adafruit_SSD1306* gfx){
    gfx->fillScreen(0x0);
    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(3);
    gfx->setTextWrap(false);
    gfx->setCursor(30, 19);
    gfx->println("2255");
    // line 2
    gfx->drawLine(18, 48, 110, 48, 1);
    // ellipse 5
    gfx->drawEllipse(64, 52, 4, 4, 1);
    // line 5
    gfx->drawLine(18, 56, 110, 56, 1);
    // line 2 copy 1
    gfx->drawLine(18, 47, 110, 47, 1);
    gfx->display();
}

void HOMING_OLED(Adafruit_SSD1306* gfx){
    gfx->fillScreen(0x0);
    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(3);
    gfx->setTextWrap(false);
    gfx->setCursor(12, 22);
    gfx->println("HOMING");
    gfx->display();
}
void RAIL_COUNT_OLED(Adafruit_SSD1306* gfx){
    gfx->fillScreen(0x0);
    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(3);
    gfx->setTextWrap(false);
    gfx->setCursor(30, 11);
    gfx->println("RAIL");
    // string 1 copy 1
    gfx->setCursor(21, 36);
    gfx->println("COUNT");
    gfx->display();
}
void RAIL_DISPLAY_COUNT(Adafruit_SSD1306* gfx, int32_t count){
    gfx->fillScreen(0x0);

    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(2);
    gfx->setTextWrap(false);
    gfx->setCursor(29, 9);
    gfx->println("COUNT:");
    // string 1 copy 1
    gfx->setTextSize(3);
    gfx->setCursor(21, 36);
    gfx->println("");
    // string 1 copy 2
    gfx->setTextSize(2);
    gfx->setCursor(30, 34);
    gfx->println(count);
    gfx->display();
}
void CENTERING_OLED(Adafruit_SSD1306* gfx){
    gfx->fillScreen(0x0);

    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(2);
    gfx->setTextWrap(false);
    gfx->setCursor(11, 29);
    gfx->println("CENTERING");
    // string 1 copy 1
    gfx->setTextSize(3);
    gfx->setCursor(21, 36);
    gfx->println("");
    gfx->display();
}

void DONE_SETUP_OLED(Adafruit_SSD1306* gfx){
    gfx->fillScreen(0x0);

    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(2);
    gfx->setTextWrap(false);
    gfx->setCursor(5, 29);
    gfx->println("DONE SETUP");
    // string 1 copy 1
    gfx->setTextSize(3);
    gfx->setCursor(21, 36);
    gfx->println("");
    gfx->display();
}

void RAIL_LENGTH_OLED(Adafruit_SSD1306* gfx, float len){
    gfx->fillScreen(0x0);
    // string 1
    gfx->setTextColor(1);
    gfx->setTextSize(2);
    gfx->setTextWrap(false);
    gfx->setCursor(29, 9);
    gfx->println("LENGTH:");
    // string 1 copy 1
    gfx->setTextSize(3);
    gfx->setCursor(21, 36);
    gfx->println("");
    // string 1 copy 2
    gfx->setTextSize(2);
    gfx->setCursor(29, 34);
    gfx->print(len);
    gfx->println("mm");
    gfx->display();
}