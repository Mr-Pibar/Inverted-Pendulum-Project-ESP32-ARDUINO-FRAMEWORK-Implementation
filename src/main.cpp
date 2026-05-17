#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

<<<<<<< Updated upstream
void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
=======
void loop(){
  moveStepLinear_primitive(DIR_PIN, STEP_PIN, 2*STEPPER_ONE_REVOLUTION, CW);
  delay(2000);
  moveStepLinear_primitive(DIR_PIN, STEP_PIN, 2*STEPPER_ONE_REVOLUTION, CCW);
  delay(2000);

>>>>>>> Stashed changes
}