#ifndef STEPPERCONTROL_H
#define STEPPERCONTROL_H

void initStepper(int dir_pin, int step_pin);

void moveStep_primitive(int dir_pin, int step_pin, int step, int dir, int speed);

void moveStepLinear_primitive(int dir_pin, int step_pin, int step, int dir);

#endif
