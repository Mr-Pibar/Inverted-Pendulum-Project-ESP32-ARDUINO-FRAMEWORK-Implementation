#include <Arduino.h>
#include <stepperControl.h>

void initStepper(int dir_pin, int step_pin){
    pinMode(dir_pin, OUTPUT);
    pinMode(step_pin, OUTPUT);
}

void moveStep_primitive(int dir_pin, int step_pin, int step, int dir, int speed){
    digitalWrite(dir_pin, dir);
    int i;

    for(i = 0; i < step; ++i){
        digitalWrite(step_pin, 1);
        delayMicroseconds(2);
        digitalWrite(step_pin, 0);
        delayMicroseconds(speed);
    }
}