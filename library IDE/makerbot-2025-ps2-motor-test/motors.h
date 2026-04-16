#include <ESP32Servo.h>


#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 5000
// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// void setPWMMotors(int c1, int c2, int c3, int c4)
// {
//   char dbg_str[30];
//   sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d",c1,c2,c3,c4);
//   Serial.println(dbg_str); 

//   pwm.setPin(PWM_CHANNEL1, c1);
//   pwm.setPin(PWM_CHANNEL2, c2);
//   pwm.setPin(PWM_CHANNEL3, c3);
//   pwm.setPin(PWM_CHANNEL4, c4);
// }

void setMotorPWM(uint8_t channel, uint16_t pwm_value) {
  pwm.setPin(channel, pwm_value);
  Serial.print("Set PWM - Channel: ");
  Serial.print(channel);
  Serial.print("\tValue: ");
  Serial.println(pwm_value);
}

void setPWMMotors(int c1, int c2, int c3, int c4) {
  Serial.printf("C1: %d\tC2: %d\tC3: %d\tC4: %d\n", c1, c2, c3, c4);
  setMotorPWM(PWM_CHANNEL1, c1);
  setMotorPWM(PWM_CHANNEL2, c2);
  setMotorPWM(PWM_CHANNEL3, c3);
  setMotorPWM(PWM_CHANNEL4, c4);
}

void initMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);
  Wire.setClock(400000);

  // setPWMMotors(0, 0, 0, 0);
  setMotorPWM(PWM_CHANNEL1, 0);
  setMotorPWM(PWM_CHANNEL2, 0);
  setMotorPWM(PWM_CHANNEL3, 0);
  setMotorPWM(PWM_CHANNEL4, 0);
  setMotorPWM(PWM_CHANNEL5, 0);
  setMotorPWM(PWM_CHANNEL6, 0);
  setMotorPWM(PWM_CHANNEL7, 0);
  setMotorPWM(PWM_CHANNEL8, 0);
}
