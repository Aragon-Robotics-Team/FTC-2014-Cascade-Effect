#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     intakeRoller,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    hopper,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    ir,                   tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

const int LATCH_DOWN = 125;
const int LATCH_UP = 220;
const int HOPPER_LOAD = 165;
const int HOPPER_SCORE = 49;

void initializeRobot() {
  return;
}

void driveTo60() {
	nMotorEncoder[rightDrive] = 0;

  motor[leftDrive] = -100;
  motor[rightDrive] = -100;

  //while(abs(nMotorEncoder[rightDrive] - ENC_RAMP_TO_60) > 50) {}	//Wait until within threshold
  wait1Msec(3000);

  motor[leftDrive] = 0;
  motor[rightDrive] = 0;
}

void liftTo60() {
	nMotorEncoder[lift] = 0;

	motor[lift] = 128;

	//while(abs(nMotorEncoder[lift] - ENC_LIFT_TO_60) > 128);
	wait1Msec(2000);

	motor[lift] = 0;
}

void turnAround() {
	motor[leftDrive] = -50;
	motor[rightDrive] = 50;

	wait1Msec(2000); //TODO replace with actual value

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

void rustle() {
	motor[leftDrive] = 50;
	motor[rightDrive] = 50;

	motor[lift] = 50;

	wait1Msec(150);

	motor[leftDrive] = -50;
	motor[rightDrive] = -50;

	motor[lift] = -50;

	wait1Msec(150);

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	motor[lift] = 0;
}

task main()
{
  initializeRobot();
  servo[hopper] = HOPPER_LOAD;
	servo[latch] = LATCH_UP;

  waitForStart(); // Wait for the beginning of autonomous phase.

  driveTo60();

  servo[latch] = LATCH_DOWN;
  wait1Msec(1000);	//Wait for latch to reach destination

  servo[hopper] = HOPPER_LOAD;
  wait1Msec(1000);

  liftTo60();

  servo[hopper] = HOPPER_SCORE;
  wait1Msec(3000);	//Wait for balls to drop in

  rustle();
  rustle();

  turnAround();

  //driveTo60(); //commented out for safety purposes

  while(true);	//Do nothing until game is done
}
