#include <SensorLib.h>
#include <SoftwareSerial.h>

//This is the serial communication contructor. This enable us to control the nodemcu(motor control).
SoftwareSerial serial(5,6);

int data = 0;
int distance = 0;

//These are the contructors for all the sensors.
//They are all named after where they are placed on the car.
const int echoFront = 10, triggerFront = 11;
Sensor sensorFront(triggerFront, echoFront);
/*
const int echoRight = 10, triggerRight = 11;
Sensor sensorRight(trigger1, echo1);
const int echoLeft = 8, triggerLeft = 9;
Sensor sensorLeft(trigger1, echo1);
*/

void findDistance(){
  distance = sensorFront.measure();
  if (distance < 25){
    data = 0;
  }
  else if (distance >= 25 & distance < 35){
    data = 1;
  }
  else if (distance >= 35){
    data = 2;
  }
}

void setup() {
  sensorFront.setupPins(triggerFront, echoFront);
  
  serial.begin(9600);
}
 
void loop() {
  findDistance();
  if(serial.available()>0)
  {
    serial.write(data);
    
  }
  serial.print("data is: ");
  serial.println(data);
}
