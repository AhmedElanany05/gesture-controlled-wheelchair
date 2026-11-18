#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
SoftwareSerial HC05(4, 5);

int16_t ax, ay, az, gx, gy, gz;
int data[2];

void setup() {
  Serial.begin(9600);
  HC05.begin(9600);
  Wire.begin();

  mpu.initialize();
  Serial.println("Transmitter ready to send data.");
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  data[0] = map(ax, -17000, 17000, 300, 400);
  data[1] = map(ay, -17000, 17000, 100, 200);

  if (ax > 10000 ) {
    HC05.println("backward");
    Serial.println("Sent: backward");
  }
  else if (ax < -10000) {
    HC05.println("forward");
    Serial.println("Sent: forward");
  }
  else if (ay > 10000) {
    HC05.println("left");
    Serial.println("Sent: left");
  }
  else if (ay < -10000) {
    HC05.println("right");
    Serial.println("Sent: right");
  }
  else {
    HC05.println("stop");
    Serial.println("Sent: stop");
  }

  delay(400);
}
