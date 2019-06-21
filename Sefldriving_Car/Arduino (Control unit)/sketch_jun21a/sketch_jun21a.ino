#include <MotorLib.h>
const int backward = true, forward = false, highSpeed = 2, lowSpeed = 1, stopMotor = 0, speedPin = 5, directionPin = 0;
Motor motor(speedPin, directionPin);
int speedIn = D8;
int directionIn = D7;

void setup() {
  motor.setupPins(speedPin, directionPin);
  pinMode(speedIn, INPUT);
  pinMode(directionIn, INPUT);
}

void loop() {
  int newSpeed = digitalRead(speedIn);
  int newDirection = digitalRead(directionIn);
  switch (speedIn) {
    case LOW:
      newSpeed = stopMotor;
      break;
      
    case HIGH:
      newSpeed = lowSpeed;
      break;
    }

  switch (directionIn){
    case LOW:
      newDirection = false;
      break;

    case HIGH:
      newDirection = true;
      break;
    }
  if (newSpeed == LOW && newDirection == LOW){
      motor.setSpeed(lowSpeed, backward);
      delay(100);
    }
  motor.setSpeed(newSpeed, newDirection);
}
