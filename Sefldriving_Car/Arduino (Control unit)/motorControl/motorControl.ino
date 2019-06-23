#include <MotorLib.h>
const int backward = true, forward = false, highSpeed = 2, lowSpeed = 1, stopMotor = 0, speedPin = 5, directionPin = 0;

int speedIn = D8;
int directionIn = D7;

Motor motor(speedPin, directionPin);

int newSpeed = 0;
bool newDirection = forward, justStopped = false;

void setup() {
  motor.setupPins(speedPin, directionPin);
  pinMode(speedIn, INPUT);
  pinMode(directionIn, INPUT);
}

void loop() {
  
  int newSpe = digitalRead(speedIn);
  int newDir = digitalRead(directionIn);
  
  switch (newSpe) {
    case LOW:
      newSpeed = stopMotor;
      break;
      
    case HIGH:
      newSpeed = lowSpeed;
      break;
    }

  switch (newDir){
    case LOW:
      newDirection = false;
      break;

    case HIGH:
      newDirection = true;
      break;
    }
  
  motor.setSpeed(newSpeed, newDirection);
}
