#include <ESP32Servo.h>
#include <analogWrite.h>
#include <tone.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>

#include <ESP32Servo.h>

static const int servoPin = 13;

Servo servo1;
Servo servo2;

void setup() {

  Serial.begin(115200);
  servo1.attach(servoPin);
}

void loop() {
 

}