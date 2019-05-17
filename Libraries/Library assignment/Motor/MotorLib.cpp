#include <MotorLib.h>

const int minSpeed = 450;
const int maxSpeed = 1020;
const int noSpeed = 0;

Motor::Motor(int speedPin, int dirPin) {
  pinMode(dirPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  
  int sPin;
  int dPin;
}

void Motor::setupPins(int speed, int direction) {
	sPin = speed;
	dPin = direction;
}

void Motor::setSpeed(int newSpeed) {
	int speed = 0;
	switch (newSpeed) {
		case 0:
			speed = noSpeed;
			break;
		case 1:
			speed = minSpeed;
			break;
		case 2:
			speed = maxSpeed;
			break;
	}
	analogWrite(sPin, speed);
}

void Motor::setSpeed(int newSpeed, bool newDirection) {
	int speed = 0;
	
	switch (newSpeed) {
		case 0:
			speed = noSpeed;
			break;
		case 1:
			speed = minSpeed;
			break;
		case 2:
			speed = maxSpeed;
			break;
	}
	if (newDirection == true) {
		digitalWrite(dPin, HIGH);
	}
	if (newDirection == false) {
		digitalWrite(dPin, LOW);
	}
	analogWrite(sPin, speed);
}
