#include <SoftwareSerial.h>
SoftwareSerial s(12 , 14);
int data = 0;

void setup() {
  s.begin(9600);
}
 
void loop() {
  
  s.write("ok");
  
  if (s.available()>0)
  {
    data=s.read();
  }
  s.println(data);
}
