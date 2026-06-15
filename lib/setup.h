#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <FastAccelStepper.h>
#include <config.h>

class Setup{
    public:
    void FAST_ACCEL_STEPPER(FastAccelStepperEngine &engine, FastAccelStepper* &stepper);
    void HOMING(FastAccelStepper* &stepper);
    void RAIL_COUNT(FastAccelStepper* &stepper, int32_t* RAIL_LENGTH);
};

#endif

