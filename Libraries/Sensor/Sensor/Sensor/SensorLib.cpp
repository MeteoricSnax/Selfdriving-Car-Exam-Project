#include <SensorLib.h>

Sensor::Sensor(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  int trigPin = triggerPin;
  int ePin = echoPin;
  int distance;
}

int Sensor::measure(){
  long duration;
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

