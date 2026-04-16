/*
 * 
 * Writen by TD
 */

#include "motors.h"
#include "PS2_controller.h"

void setup()
{
  Serial.begin(115200);
  pwm.begin();          
  pwm.setPWMFreq(60);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void loop()
{
  // ps2x.read_gamepad(0, 0);
  // // PS2control();
  // controlServoWithPad();
  pwm.setPWM(CHANNEL6, 0, SERVOMIN); // Quay ngược tối đa
  pwm.setPWM(CHANNEL7, 0, SERVOMAX); // Quay thuận tối đa
  delay(50);
  
}
