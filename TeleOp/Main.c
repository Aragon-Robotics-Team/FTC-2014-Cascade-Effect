#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     blDrive,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     brDrive,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     flDrive,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frDrive,       tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot() {

  return;
}

void drive()
{
	if(abs(joystick.joy1_y1) > 8)
 	{
 		motor[flDrive] = joystick.joy1_y1;
 		motor[blDrive] = joystick.joy1_y1;
	}
	else
	{
		motor[flDrive] = 0;
		motor[blDrive] = 0;
	}
 	if(abs(joystick.joy1_y2) > 8)
 	{
 		motor[frDrive] = joystick.joy1_y2;
 		motor[brDrive] = joystick.joy1_y2 * .95;
	}
	else
	{
		motor[frDrive] = 0;
		motor[brDrive] = 0;
	}
}

task main() {

  initializeRobot();

  waitForStart();

  while(true) {
  	getJoystickSettings(joystick);
  }
}
