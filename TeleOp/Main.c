#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
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

/*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


const int DEADBAND = 8;	//1/16th deadband for the terrible gamepads
const float CREEP_SPEED = 0.5;	//Power multiplier, must be between -1 and 1 (negative for inverted controls
const int GRABBER_DOWN = 125;
const int GRABBER_UP = 220;
const int HOPPER_LOAD = 165;
const int HOPPER_SCORE = 49;

void initializeRobot() {

  return;
}

void drive(float power) {
	if(abs(joystick.joy1_y1) > DEADBAND) {
 		motor[frontLeftDrive] = joystick.joy1_y1 * power;
 		motor[backLeftDrive] = joystick.joy1_y1 * power;
	}
	else {
		motor[frontLeftDrive] = 0;
		motor[backLeftDrive] = 0;
	}
 	if(abs(joystick.joy1_y2) > DEADBAND) {
 		motor[frontRightDrive] = joystick.joy1_y2 * power;
 		motor[backRightDrive] = joystick.joy1_y2 * power;
	}
	else {
		motor[frontRightDrive] = 0;
		motor[backRightDrive] = 0;
	}
}


void grabber() { //Migrate to joy2 for Dual Drivers
	if(joy1Btn(2))
		servo[latch] = GRABBER_DOWN;
	else if(joy1Btn(4))
		servo[latch] = GRABBER_UP;	//Upright
}

void outtake() {	//Migrate to joy2 for Dual Drivers
	if(joy1Btn(6))	//Right Bumper
		servo[hopper] = HOPPER_SCORE;
	else if(joy1Btn(8)) //Right Trigger
		servo[hopper] = HOPPER_LOAD;
}

void rollers() {	//Migrate to joy2 for Dual Drivers
	if(joy1Btn(1))
		motor[intakeRoller] = 96;
	else
		motor[intakeRoller] = 0;//Migrate to joy2 for Dual Drivers
}

void liftManual() {	//Migrate to joy2 for Dual Drivers
	if(joystick.joy1_TopHat == 0)
		motor[lift] = 128;
	else if(joystick.joy1_TopHat == 4)
		motor[lift] = -96;
	else if(joystick.joy1_TopHat == -1)
		motor[lift] = 0;
}

/*void liftAuto() {
	if(joy2Btn(5)) {
		if(nMotorEncoder[lift] > LOWCONST)
			moto[lift] = -96;
		else if(nMotorEncoder < LOWCONST)
			motor[lift] = 96;
		else
			motor[lift] = 0;
	}
}*/

/*void liftManualAna() {
	if(abs(joystick.joy2_y1) > 32)
		motor[lift] = joystick.joy2_y1;
}*/

task main() {

  initializeRobot();

  waitForStart();

  while(true) {
  	getJoystickSettings(joystick);

  	if(joy1Btn(5))	//Left trigger for creep speed
  		drive(CREEP_SPEED);
  	else
  		drive(1);
  	grabber();
  	outtake();
  	rollers();
  	liftManual();
  }
}
