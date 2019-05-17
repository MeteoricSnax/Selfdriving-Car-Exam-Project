#include <MotorLib.h>

const int stopMotor = 0;
const int lowSpeed = 1;
const int highSpeed = 2;
const int forward = true;
const int backward = false;

const int speedPin = 5;
const int directionPin = 0;
Motor motor(speedPin, directionPin);

void setup() {
  motor.setupPins(speedPin, directionPin);
}

void loop() {
  motor.setSpeed(stopMotor, forward);
}
