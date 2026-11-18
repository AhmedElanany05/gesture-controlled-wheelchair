#include <SoftwareSerial.h>

SoftwareSerial HC05(8, 9);
const int enbA = 3;
const int enbB = 5;

const int IN1 = 2;
const int IN2 = 4;
const int IN3 = 7;
const int IN4 = 6;

int RightSpd = 160;
int LeftSpd = 160;

String receivedData = "";

void setup() {
  Serial.begin(9600);
  HC05.begin(9600);
  Serial.println("Receiver ready to receive data.");

  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  while (HC05.available()) {
    char incomingChar = HC05.read();
    receivedData += incomingChar;

    if (incomingChar == '\n') {
      receivedData.trim();
      Serial.print("Received data: ");
      Serial.println(receivedData);

      if (receivedData == "forward") {
        Serial.println("Moving forward");
        moveForward();
      }
      else if (receivedData == "backward") {
        Serial.println("Moving backward");
        moveBackward();
      }
      else if (receivedData == "left") {
        Serial.println("Turning left");
        moveLeft();
      }
      else if (receivedData == "right") {
        Serial.println("Turning right");
        moveRight();
      }
      else if (receivedData == "stop") {
        Serial.println("Stopping motors");
        stopMotors();
      }
      else {
        Serial.println("Invalid command received");
      }

      receivedData = "";
    }
  }
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enbA, RightSpd);
  analogWrite(enbB, LeftSpd);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enbA, RightSpd);
  analogWrite(enbB, LeftSpd);
}

void moveLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enbA, RightSpd);
  analogWrite(enbB, LeftSpd);
}

void moveRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enbA, RightSpd);
  analogWrite(enbB, LeftSpd);
}

void stopMotors() {
  analogWrite(enbA, 0);
  analogWrite(enbB, 0);
}
