#include <SensorLib.h>
#include <Servo.h>

const int servoPin = 2; //Attached servo on pin D7
const int motorDirection = 3; //Motor direction
const int motorSpeed = 4; // Motor speed
const int stopMotor = 0, startMotor = 1;

const int posRight = 110, const int posLeft = 50, const int posStraight = 80;

const int leftEcho = 12, leftTrigger = 13;
const int frontEcho = 10, frontTrigger = 11;
const int rightEcho = 8, rightTrigger = 9;
int distanceLeft = 0, int distanceFront = 0, int distanceRight = 0;
int distanceThreshold = 40;
const unsigned long waitTime = 300;

Sensor sensorLeft(leftEcho, leftTrigger);
Sensor sensorFront(frontEcho, frontTrigger);
Sensor sensorRight(rightEccho, rightTrigger);
Servo servo;

int state = 1;

void setup() {
  pinMode(motorDirection, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  sensorLeft.setupPins(leftEcho, leftTrigger);
  sensorFront.setupPins(frontEcho, frontTrigger);
  sensorRight.setupPins(rightEccho, rightTrigger);
}

void loop() {
  if (digitalRead(dangerpin) == HIGH) { // Initiate danger sequence
    reverse();
    delay(800);

    brake();
    left();
    delay(500);

    reverse();
    delay(800);

    brake();
    right();
    delay(500);

    go();
    delay(800);
    
    brake();
    straight();
    delay(500);

    state = 1;
  } else if (state == 1) {
    go();
    state = 0;
  } else {
    return;
  }
}

void left() {
  servo.attach(servoPin);
  delay(300);
  servo.write(posLeft); // Position for front wheels
  delay(600);
  servo.detach();
}

void right() {
  servo.attach(servoPin);
  delay(300);
  servo.write(posRight); // Position for front wheels
  delay(600);
  servo.detach();
}

void straight() {
  servo.attach(servoPin);
  delay(300);
  servo.write(posStraight); // Position for front wheels
  delay(600);
  servo.detach();
}

void reverseLeft() {
  // Make it go resverse and left, so that means wheels turn right  
}

void reverseRight() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  servo.attach(servoPin);
  servo.write(posRight);
  wait();
  servo.detach();
}

void wait() {
  unsigned long currentTime = millis();
  while (millis() <= currentTime + waitTime && leave = false) {
    distanceLeft = sensorLeft.measure();
    distanceFront = sensorFront.measure();
    distanceRight = sensorRight.measure();
    if (distanceRight < distanceThreshold 
        && distanceFront < distanceThreshold
        && distanceLeft < distanceThreshold) {
      leave = true;
    }
  }
}
