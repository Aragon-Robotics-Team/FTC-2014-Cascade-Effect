#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     intakeRoller,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightDrive, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backLeftDrive, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backRightDrive, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     lift,          tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     frontLeftDrive, tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    hopper,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot() {

  return;
}

void drive() {
	if(abs(joystick.joy1_y1) > 8) {
 		motor[frontLeftDrive] = joystick.joy1_y1;
 		motor[backLeftDrive] = joystick.joy1_y1;
	}
	else {
		motor[frontLeftDrive] = 0;
		motor[backLeftDrive] = 0;
	}
 	if(abs(joystick.joy1_y2) > 8) {
 		motor[frontRightDrive] = joystick.joy1_y2;
 		motor[backRightDrive] = joystick.joy1_y2;
	}
	else {
		motor[frontRightDrive] = 0;
		motor[backRightDrive] = 0;
	}
}


void grabber() {
	if(joy1Btn(2))
		servo[latch] = 40;
	else if(joy1Btn(4))
		servo[latch] = 200;
}

void outtake() {
	if(joy1Btn(1))
		servo[hopper] = 40;
	else if(joy1Btn(3))
		servo[hopper] = 200
}

void rollers() {
	bool isRunning;
	if(joy2Btn(2)) {
		if(isRunning)
			isRunning = false;
		else
			isRunning = true;
	}
	wait1Msec(25);
	if(isRunning)
		motor[intakeRoller] = 96;
	else
		motor[intakeRoller] = 0;
}

task main() {

  initializeRobot();

  waitForStart();

  while(true) {
  	getJoystickSettings(joystick);
  	drive();
  	grabber();
  	outtake();
  }
}
