#include <Arduino.h>
#include <config.h>
#include "stepperControl.h"

void setup(){
  initStepper(DIR_PIN, STEP_PIN);
  delay(1000);
}

void loop(){
  moveStep_primitive(DIR_PIN, STEP_PIN, STEPPER_ONE_REVOLUTION, CW, SPEED_DELAY);
  delay(2000);
  moveStep_primitive(DIR_PIN, STEP_PIN, STEPPER_ONE_REVOLUTION, CCW, SPEED_DELAY);
  delay(2000);
}