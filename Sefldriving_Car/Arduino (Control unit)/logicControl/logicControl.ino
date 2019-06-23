#include <Servo.h>

const int servoPin = 2;       //Attached servo on pin D7
const int motorDirection = 3; //Motor direction
const int motorSpeed = 4;     // Motor speed

const int servoRight = 130, servoLeft = 50, servoStraight = 90; // Servo directions (in degrees)

const int rightEcho = 13, rightTrigger = 12;
const int frontEcho = 10, frontTrigger = 11;
const int leftEcho = 9, leftTrigger = 8;
const int rearEcho = 6, rearTrigger = 7;
int distanceLeft = 0, distanceFront = 0, distanceRight = 0, distanceRear = 0;
const int distanceThreshold = 20;
const unsigned long waitTime = 100, waitTimeMulti = 10;

int state = 0;

Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
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

// 0 = nothing is close enough | 1 = front | 2 = left | 3 = right | 4 = rear
void loop()
{
  Serial.println("start of navigation loop!");
  state = findClosest();
  Serial.println(state);
  if (state == 0){
    straight();
    }

  if (state == 1) {
    reverseStraight();
    int l = measure(leftTrigger, leftEcho);
    int r = measure(rightTrigger, rightEcho);
    if (r > l)
    {
      reverseLeft();
      right();
    }
    else if (r < l)
    {
      reverseRight();
      left();
    }
  }

  if (state == 2) {
    reverseRight();
    Serial.println("hello from case 2 reverse");
    left();
    Serial.println("hello from case 2");
  }

  if (state == 3) {
    reverseLeft();
    Serial.println("hello from case 3 reverse");
    right();
    Serial.println("hello from case 3");
  }

  if (state == 4) {
    straight();
  }
}

void left()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  //servo.attach(servoPin);
  servo.write(servoLeft);
  //servo.detach();
  Serial.println("left");
  waitFront();
}

void right()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  //servo.attach(servoPin);
  servo.write(servoRight);
  //servo.detach();
  Serial.println("right");
  waitFront();
}

void straight()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, HIGH);
  //servo.attach(servoPin);
  servo.write(servoStraight);
  //servo.detach();
  Serial.println("straight");
  waitFront();
}

void reverseStraight()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  //servo.attach(servoPin);
  servo.write(servoStraight);
  //servo.detach();
  Serial.println("reverseStraight");
  waitRear();
}

void reverseLeft()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  //servo.attach(servoPin);
  servo.write(servoLeft);
  //servo.detach();
  Serial.println("reverseLeft");
  waitRear();
}

void reverseRight()
{
  digitalWrite(motorSpeed, HIGH);
  digitalWrite(motorDirection, LOW);
  //servo.attach(servoPin);
  servo.write(servoRight);
  //servo.detach();
  Serial.println("reverseRight");
  waitRear();
}

void waitFront()
{
  unsigned long currentTime = millis();
  bool tooClose = false;
  while (millis() <= currentTime + (waitTime * waitTimeMulti) && tooClose == false)
  {
    distanceLeft = measure(leftTrigger, leftEcho);
    distanceFront = measure(frontTrigger, frontEcho);
    distanceRight = measure(rightTrigger, rightEcho);
    delay(100);
    if (distanceRight < distanceThreshold || distanceFront < distanceThreshold || distanceLeft < distanceThreshold)
    {
      tooClose = true;
    }
  }
  Serial.println("waitFront");
}

void waitRear()
{
  unsigned long currentTime = millis();
  bool tooClose = false;
  while (millis() <= currentTime + (waitTime * waitTimeMulti) && tooClose == false)
  {
    distanceRear = measure(rearTrigger, rearEcho);
    delay(100);
    if (distanceRear < distanceThreshold)
    {
      tooClose = true;
    }
  }
  Serial.println("waitRear");
}

int measure(int trigPin, int ePin)
{
  int distance = 0;
  long duration = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(ePin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

// findClosest finds what sensor is closest to something and return a int based on what sensor it is.
// 0 = nothing is close enough | 1 = front | 2 = left | 3 = right | 4 = rear
int findClosest()
{
  int distFront = measure(frontTrigger, frontEcho);
  delayMicroseconds(10);
  Serial.print("front is: ");
  Serial.println(distFront);
  int distLeft = measure(leftTrigger, leftEcho);
  delayMicroseconds(10);
  Serial.print("left is: ");
  Serial.println(distLeft);
  int distRight = measure(rightTrigger, rightEcho);
  delayMicroseconds(10);
  Serial.print("right is: ");
  Serial.println(distRight);
  int distRear = measure(rearTrigger, rearEcho);
  delayMicroseconds(10);
  Serial.print("rear is: ");
  Serial.println(distRear);
  int closest = distFront, closestSensor = 1;
  if (closest > distLeft)
  {
    closest = distLeft;
    closestSensor = 2;
  }
  if (closest > distRight)
  {
    closest = distRight;
    closestSensor = 3;
  }
  if (closest > distRear)
  {
    closest = distRear;
    closestSensor = 4;
  }
  
  Serial.print("closest is: ");
  Serial.println(closestSensor);
  if (closest > distanceThreshold)
  {
    closestSensor = 0;
  }
  return closestSensor;
}
