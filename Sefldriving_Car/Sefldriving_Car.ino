
const int sensor1[2] = {9, 10}; //[0] is the trigger pin, and [1] is the echo pin

void setup() {
  pinMode(sensor1[0], OUTPUT); // Sets the trigPin as an Output
  pinMode(sensor1[1], INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  sensor(sensor1[0], sensor1[1]);
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
