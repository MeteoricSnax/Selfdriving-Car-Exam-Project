#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial s(3,1);
int data;

void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(9600);
}

void loop(){
  readData();
}

void sendData() {
  //Write '123' to Serial
  s.write(123);
  delay(1000);
}

void readData() {
  data = s.read(); //Read the serial data and store it
  s.print(data);
  delay(1000);
}
