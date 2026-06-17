#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <FastAccelStepper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <config.h>
#include <setup.h>
#include <oled.h>

//primary containers

FastAccelStepperEngine ENGINE = FastAccelStepperEngine();
FastAccelStepper* STEPPER = nullptr;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Setup SETUP;
int32_t rail_count;

void setup(){
  Serial.begin(115200);
  SETUP.OLED(&display);
  SETUP.FAST_ACCEL_STEPPER(ENGINE, STEPPER);
  SETUP.HOMING(STEPPER, &display);
  SETUP.RAIL_COUNT(STEPPER, &rail_count, &display);

  RAIL_LENGTH_OLED(&display, (float)((float)(rail_count) / (float)STEPS_PER_MM));

  STEPPER->setSpeedInHz(3000);
  STEPPER->setAcceleration(1500);

}


void loop(){
  if(Serial.available() && STEPPER){
    int n_revolution = Serial.parseInt();

    STEPPER->move(ONE_REV_STEPPER * n_revolution);
    Serial.println("Moving");
    Serial.print(n_revolution);
  }
}