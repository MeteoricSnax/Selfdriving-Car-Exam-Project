//// Servo setup
#include <Servo.h>
Servo servo;

int posright = 110; //Postion for front wheels when turning right
int posleft = 50;   //Postion for front wheels when turning left
int posstraight = 80; //Postion for front wheels when going straight forward

int servopin = D7; //Attached servo on pin D7
int dangerpin = D8; // Danger signal pin D8 fron Arduino UNO

// Motor setup
int motorPin = D6;
int motorDirection = 0; //Motor direction
int motorSpeed = 5; // Motor speed
int state = 1;
int danager;
void setup() {
  Serial.begin(9600);
  Serial.flush();
  // Pin setup
  pinMode(motorPin, OUTPUT);
  pinMode(motorDirection, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(dangerpin, INPUT);

  //Adjust speed of motors
  analogWrite(motorSpeed, 900); // Max is 1040

  go(); // All systems go
}

void loop() {

  danager = digitalRead(dangerpin);
  if (danager == HIGH) { // Initiate danger sequence
    reverse();
    delay(800);

    brake();
    left();
    delay(500);

    reverse();
    delay(800);

    brake();
    right();
    delay(500);
    while (true) {
      if (digitalRead(dangerpin) == HIGH) {
        reverse();
        delay(400);
        brake();
        right();
        delay(500);
        Serial.println("not break");
      } else {
        go();
        Serial.println("break");
        break;
      }
    }
    delay(800);

    brake();
    straight();
    delay(500);

    state = 1;
  } else if (state == 1) {
    go();
    state = 0;
  } else {
    return;
  }
}


void brake() {
  digitalWrite(motorPin, HIGH);
}

void go() {
  digitalWrite(motorPin, LOW);
  digitalWrite(motorDirection, HIGH);
}

void reverse() {
  digitalWrite(motorPin, LOW);
  digitalWrite(motorDirection, LOW);
}

void left() {
  servo.attach(servopin);
  delay(300);
  servo.write(posleft); // Position for front wheels
  delay(600);
  servo.detach();
}

void right() {
  servo.attach(servopin);
  delay(300);
  servo.write(posright); // Position for front wheels
  delay(600);
  servo.detach();
}

void straight() {
  servo.attach(servopin);
  delay(300);
  servo.write(posstraight); // Position for front wheels
  delay(600);
  servo.detach();
}
