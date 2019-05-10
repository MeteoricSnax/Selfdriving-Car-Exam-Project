#include <Servo.h>
Servo servo;  
int servo1 = 16; //this is the servo motor that control the sensor group on the roof of the car. GPIO 16 / D0
int servo2= 5; //this is the servo motor that controls the steering. GPIO 5 / D1
int servoAngle = 0;   // servo position in degrees. This goes from 0 to 180
const int sensor1[2] = {15, 13}; //[0] is the trigger pin (D8 / GPIO-15), and [1] is the echo pin (D7 / GPIO-13). 
const int sensor2[2] = {12, 14}; //[0] is the trigger pin (D6 / GPIO-12), and [1] is the echo pin (D5 / GPIO-14).
const int sensor3[2] = {2, 0}; //[0] is the trigger pin (D4 / GPIO-15), and [1] is the echo pin (D3 / GPIO-00).

void setup() {
  servoSteer.attach(servo2);
  servoSensor.attach(servo1);
  pinMode(sensor1[0], OUTPUT); // Sets the trigPin as an Output
  pinMode(sensor1[1], INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  sensor(sensor1[0], sensor1[1]);
  servoSteer.write(90);
  servoSensor.write(90);
  //motor run
  //motor stop
}

int sensor(int trigger, int echo) {
  
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}
