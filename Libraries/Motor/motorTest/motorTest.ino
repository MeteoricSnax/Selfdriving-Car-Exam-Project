#include <MotorLib.h>
#include <Servo.h>
const int backward = true, forward = false, highSpeed = 2, lowSpeed = 1, stopMotor = 0, speedPin = 5, directionPin = 0;
Motor motor(speedPin, directionPin);
Servo servo;  
int servoPin = 16;

void setup() {
  motor.setupPins(speedPin, directionPin);
  Serial.begin(9600);  
  servo.attach(servoPin);
}

void loop() {
  motor.setSpeed(stopMotor, forward);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(135);
  delay(1000);
  servo.write(145);
  delay(1000);
  servo.write(65);
  delay(1000);
  servo.write(55);
}
