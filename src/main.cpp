#include <Arduino.h>
#include <FastAccelStepper.h>
#include <config.h>
#include <setup.h>

//primary containers

FastAccelStepperEngine ENGINE = FastAccelStepperEngine();
FastAccelStepper* STEPPER = nullptr;

Setup SETUP;
int32_t rail_count;

void setup(){
  Serial.begin(115200);
  SETUP.FAST_ACCEL_STEPPER(ENGINE, STEPPER);
  SETUP.HOMING(STEPPER);
  SETUP.RAIL_COUNT(STEPPER, &rail_count);
}


void loop(){
  if(Serial.available() && STEPPER){
    int n_revolution = Serial.parseInt();

    STEPPER->move(ONE_REV_STEPPER * n_revolution);
    Serial.println("Moving");
    Serial.print(n_revolution);
  }
}