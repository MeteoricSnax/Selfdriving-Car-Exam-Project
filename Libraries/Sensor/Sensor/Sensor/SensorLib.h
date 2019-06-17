#ifndef SensorLib_h
#define SensorLib_h

#include <Arduino.h>

class Sensor {
  public:
    Sensor(int triggerPin, int echoPin);

    int measure();


  private:
  int trigPin;
  int ePin;
  int distance;
};

#endif
