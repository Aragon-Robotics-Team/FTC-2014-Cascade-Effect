#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     intakeRoller,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightDrive, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backLeftDrive, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backRightDrive, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     frontLeftDrive, tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    hopper,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
  //NOT ALLOWED TO USE; NEED STICKER

  return;
}

const int GRABBER_DOWN = 125;
const int GRABBER_UP = 220;
const int HOPPER_LOAD = 165;
const int HOPPER_SCORE = 49;
const int ENC_RAMP_TO_60 = 8000;
const int ENC_60_TO_PARK = 840;	//TODO: Measure this value. Current value is standing in so code will compile
const int ENC_LIFT_TO_60 = 4000;	//TODO: Measure this value. Current value is standing in so code will compile

void driveTo60() {
	nMotorEncoder[backRightDrive] = 0;

  motor[frontLeftDrive] = -100;
  motor[backLeftDrive] = -100;
  motor[frontRightDrive] = -100;
  motor[backRightDrive] = -100;

  //while(abs(nMotorEncoder[backRightDrive] - ENC_RAMP_TO_60) > 50) {}	//Wait until within threshold
  wait1Msec(3000);

  motor[frontLeftDrive] = 0;
  motor[backLeftDrive] = 0;
  motor[frontRightDrive] = 0;
  motor[backRightDrive] = 0;
}

void liftTo60() {
	nMotorEncoder[lift] = 0;

	motor[lift] = 128;

	//while(abs(nMotorEncoder[lift] - ENC_LIFT_TO_60) > 128);
	wait1Msec(2000);

	motor[lift] = 0;
}

void turnToParking() {
	motor[frontLeftDrive] = -96;
	motor[backLeftDrive]  = -96;
	motor[frontRightDrive] = 96;
	motor[backRightDrive] = 96;

	wait1Msec(840);	//TODO: Measure value. Current is standin so code compiles

	motor[frontLeftDrive] = 0;
  motor[backLeftDrive] = 0;
  motor[frontRightDrive] = 0;
  motor[backRightDrive] = 0;
}

void driveAndPark() {
	nMotorEncoder[backRightDrive] = 0;

  motor[frontLeftDrive] = -100;
  motor[backLeftDrive] = -100;
  motor[frontRightDrive] = -100;
  motor[backRightDrive] = -100;

  while(abs(nMotorEncoder[backRightDrive] - ENC_60_TO_PARK) > 50);	//Wait until within threshold

  motor[frontLeftDrive] = 0;
  motor[backLeftDrive] = 0;
  motor[frontRightDrive] = 0;
  motor[backRightDrive] = 0;
}

void rustle() {
	motor[frontLeftDrive] = 50;
	motor[backLeftDrive] = 50;
	motor[frontRightDrive] = 50;
	motor[backRightDrive] = 50;

	motor[lift] = 50;

	wait1Msec(150);

	motor[frontLeftDrive] = -50;
	motor[backLeftDrive] = -50;
	motor[frontRightDrive] = -50;
	motor[backRightDrive] = -50;

	motor[lift] = -50;

	wait1Msec(150);

	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;
	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;

	motor[lift] = 0;
}

task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  servo[latch] = GRABBER_UP;

  driveTo60();

  servo[latch] = GRABBER_DOWN;
  wait1Msec(1000);	//Wait for latch to reach destination

  servo[hopper] = HOPPER_LOAD;
  wait1Msec(1000);

  liftTo60();

  servo[hopper] = HOPPER_SCORE;
  wait1Msec(3000);	//Wait for balls to drop in

  rustle();
  rustle();

  /*turnToParking();

  driveAndPark();
  */
  while(true);	//Do nothing until game is done
}
