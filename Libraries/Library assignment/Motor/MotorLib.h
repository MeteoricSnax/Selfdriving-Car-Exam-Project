#ifndef MotorLib_h
#define MotorLib_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int speedPin, int dirPin);

	void setupPins(int speed, int direction);
	void setSpeed(int newSpeed);
	void setSpeed(int newSpeed, bool newDirection);
	int sPin;
	int dPin;
  private:
	
};

#endif
