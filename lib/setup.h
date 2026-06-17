#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <FastAccelStepper.h>
#include <config.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Setup{
    public:
    void FAST_ACCEL_STEPPER(FastAccelStepperEngine &engine, FastAccelStepper* &stepper);
    void HOMING(FastAccelStepper* &stepper, Adafruit_SSD1306* display);
    void RAIL_COUNT(FastAccelStepper* &stepper, int32_t* RAIL_LENGTH, Adafruit_SSD1306* display);
    void OLED(Adafruit_SSD1306* display);
};

#endif

