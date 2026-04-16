#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class object
#define BEBUG_CTRL

// calibration for different kinds of PS2 controller, this value only suitable for the PS2 controller comes with VRC2023 K12 Maker kit 
#define X_JOY_CALIB 127
#define Y_JOY_CALIB 128

#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18

#define TOP_SPEED 4095
#define NORM_SPEED 2048
#define TURNING_FACTOR 1

#define SINGLE_HAND_DRIVING 0
#define TWO_HAND_DRIVING 1

// Giới hạn pulse an toàn cho servo
#define SERVOMIN 110     // Xung ngắn nhất (quay ngược tối đa)
#define SERVOMAX 600     // Xung dài nhất (quay thuận tối đa)
#define SERVO_STOP 375   // Xung giữa (dừng servo)

#define CHANNEL6 6       // Servo 6
#define CHANNEL7 7       // Servo 7

bool driving_mode = SINGLE_HAND_DRIVING;

void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }

}

// void linear(int speed) {
//   if (ps2x.Button(PSB_PAD_UP)) {
//     setMotorPWM(12, speed);
//   }
//   else if (ps2x.Button(PSB_PAD_DOWN)) {
//     setMotorPWM(13, speed);
//   }
//   delay(100);
// }

void controlServoWithPad() {
  // Điều khiển 2 servo ngược chiều khi nhấn D-PAD
  if (ps2x.Button(PSB_PAD_UP)) {
    pwm.setPWM(CHANNEL6, 0, SERVOMAX);
    pwm.setPWM(CHANNEL7, 0, SERVOMIN);
  } 
  else if (ps2x.Button(PSB_PAD_DOWN)) {
    pwm.setPWM(CHANNEL6, 0, SERVOMIN);
    pwm.setPWM(CHANNEL7, 0, SERVOMAX);
  }
  else {
    pwm.setPWM(CHANNEL6, 0, SERVO_STOP);
    pwm.setPWM(CHANNEL7, 0, SERVO_STOP);
  }
}

bool PS2control() {
  int speed = TOP_SPEED;
  if (ps2x.Button(PSB_R2))
    speed = NORM_SPEED;
  if (ps2x.ButtonPressed(PSB_SELECT))
    driving_mode =! driving_mode;
  
  int rawY = ps2x.Analog(PSS_LY);
  int rawRX = ps2x.Analog(PSS_RX);
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  // Chuẩn hóa từ 0–255 về -1.0 đến +1.0
  double y = -((rawY - 128) / 128.0);  // Cần trái, tiến/lùi (đảo chiều)
  double rx = -((rawRX - 128) / 128.0);   // Cần phải, quay

  y = constrain(y, -1.0, 1.0);
  rx = constrain(rx, -1.0, 1.0);

  double leftPower = y + rx;
  double rightPower = y - rx;

  leftPower = constrain(leftPower, -1.0, 1.0);
  rightPower = constrain(rightPower, -1.0, 1.0);

  if (leftPower > 0) {
    c2 = map(leftPower * 1000, 0, 1000, 0, speed);
  } else if (leftPower < 0) {
    c1 = map(-leftPower * 1000, 0, 1000, 0, speed);
  }

  if (rightPower > 0) {
    c3 = map(rightPower * 1000, 0, 1000, 0, speed);
  } else if (rightPower < 0) {
    c4 = map(-rightPower * 1000, 0, 1000, 0, speed);
  }
  setPWMMotors(c1, c2, c3, c4);

  controlServoWithPad();



  // if(nJoyX == -1 && nJoyY == 0) // in case of lost connection with the wireless controller, only used in VRC2023 PS2 wireless controller 
  // {
  //   setPWMMotors(0, 0, 0, 0);
  //   return 0;
  // }

  // bool temp = (nJoyY * nJoyX > 0);
  // if (nJoyX) // Turning
  // {
  //   nMotMixL = -nJoyX + (nJoyY * temp);
  //   nMotMixR = nJoyX + (nJoyY * !temp);
  // }
  // else // Forward or Reverse
  // {
  //   nMotMixL = nJoyY;
  //   nMotMixR = nJoyY;
  // }
  // #ifdef BEBUG_CTRL
  // Serial.print(F("Calculated value from joystick: "));
  // Serial.print(nMotMixL);
  // Serial.print("\t");
  // Serial.println(nMotMixR);
  // #endif
  // int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  // if (nMotMixR > 0)
  // {
  //   c3 = nMotMixR;
  //   c3 = map(c3, 0, 128, 0, speed);
  // }

  // else if (nMotMixR < 0)
  // {
  //   c4 = abs(nMotMixR) + 1;
  //   c4 = map(c4, 0, 128, 0, speed);
  // }

  // if (nMotMixL > 0)
  // {
  //   c1 = nMotMixL;
  //   c1 = map(c1, 0, 128, 0, speed);
  // }
  // else if (nMotMixL < 0)
  // {
  //   c2 = abs(nMotMixL);
  //   c2 = map(c2, 0, 128, 0, speed);
  // }
  // setPWMMotors(c1, c2, c3, c4);
  return 1;
}
