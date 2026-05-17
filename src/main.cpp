#include <Arduino.h>
#include <config.h>
#include "wifiAndMQTT.h"
#include <stepperControl.h>
#include <connectivity.h>

void setup(){
  Serial.begin(9600);
  initStepper(DIR_PIN, STEP_PIN);
  initWifi();
  initMQTT();
  delay(1000);
}

void loop(){
  reconnectMQTT();
  updateMQTT();
  if(step_mqtt > 0){
    moveStepLinear_primitive(DIR_PIN, STEP_PIN, step_mqtt, dir_mqtt);
    step_mqtt = 0;
  }
  delay(100);
}