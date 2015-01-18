#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     ,              tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     ,              tmotorNone, openLoop)

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot() {
  return;
}


task main() {

  initializeRobot();

  waitForStart();

  while(true) {

  }
}
