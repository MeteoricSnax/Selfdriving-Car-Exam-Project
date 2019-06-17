#include <SensorLib.h>


const int echo1 = 12, trigger1 = 13;
int distance1 = 0;

Sensor sensor1(trigger1, echo1);

void setup() {
  sensor1.setupPins(trigger1, echo1);
  Serial.begin(9600);
}

void loop() {
  distance1 = sensor1.measure();
  Serial.print("Distance: ");
  Serial.println(distance1);
  delay(100);
}
