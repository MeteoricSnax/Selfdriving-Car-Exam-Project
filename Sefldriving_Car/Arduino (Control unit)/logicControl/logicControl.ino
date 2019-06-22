#include <Servo.h>

const int servoPin = 2; //Attached servo on pin D7
const int motorDirection = 3; //Motor direction
const int motorSpeed = 4; // Motor speed

const int servoRight = 110;
const int servoLeft = 50;
const int servoStraight = 80;

const int rightEcho = 13, rightTrigger = 12;
const int frontEcho = 10, frontTrigger = 11;
const int leftEcho = 9, leftTrigger = 8;
const int rearEcho = 6, rearTrigger = 7;
int distanceLeft = 0, distanceFront = 0, distanceRight = 0, distanceRear = 0;
int distanceThreshold = 40;
const unsigned long waitTime = 600;
int state = 0;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(motorDirection, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(leftTrigger, OUTPUT);
  pinMode(leftEcho, INPUT);
  pinMode(frontTrigger, OUTPUT);
  pinMode(frontEcho, INPUT);
  pinMode(rightTrigger, OUTPUT);
  pinMode(rightEcho, INPUT);
  pinMode(rearTrigger, OUTPUT);
  pinMode(rearEcho, INPUT);
}

void loop() {
  left();
  right();
  straight();
  reverseStraight();
  reverseLeft();
  reverseRight();
}

void left(){
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  servo.attach(servoPin);
  servo.write(servoLeft); // Position for front wheels
  wait();
  servo.detach();
}

void right() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  servo.attach(servoPin);
  servo.write(servoRight); // Position for front wheels
  wait();
  servo.detach();
}

void straight() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  servo.attach(servoPin);
  servo.write(servoStraight); // Position for front wheels
  wait();
  servo.detach();
}

void reverseStraight() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  servo.attach(servoPin);
  servo.write(servoStraight);
  wait();
  servo.detach();
}

void reverseLeft() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  servo.attach(servoPin);
  servo.write(servoLeft);
  wait();
  servo.detach();
}

void reverseRight() {
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  servo.attach(servoPin);
  servo.write(servoRight);
  wait();
  servo.detach();
}

void wait() {
  unsigned long currentTime = millis();
  bool leave = false;
  while (millis() <= currentTime + waitTime && leave == false) {
    distanceLeft = measure(leftTrigger, leftEcho);
    Serial.print("left: ");
    Serial.println(distanceLeft);
    distanceFront = measure(frontTrigger, frontEcho);
    Serial.print("front: ");
    Serial.println(distanceFront);
    distanceRight = measure(rightTrigger, rightEcho);
    Serial.print("right: ");
    Serial.println(distanceRight);
    distanceRear = measure(rearTrigger, rearEcho);
    Serial.print("rear: ");
    Serial.println(distanceRear);
    if (distanceRight < distanceThreshold 
        || distanceFront < distanceThreshold
        || distanceLeft < distanceThreshold || 
        distanceRear < distanceThreshold) {
      leave = true;
    }
  }
}

int measure(int trigPin, int ePin){
  int distance = 0;
  long duration = 0;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ePin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}
