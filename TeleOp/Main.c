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

/*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

const int DEADBAND = 32;	//1/16th deadband for the terrible gamepads
const int LATCH_DOWN = 125;
const int LATCH_UP = 220;
const int HOPPER_LOAD = 165;
const int HOPPER_AIM = 100;
const int HOPPER_SCORE = 45;

void initializeRobot() {
  return;
}

void drive(float power) {
	if(abs(joystick.joy1_y1) > DEADBAND)
 		motor[leftDrive] = joystick.joy1_y1 * power;
	else
		motor[leftDrive] = 0;
 	if(abs(joystick.joy1_y2) > DEADBAND)
 		motor[rightDrive] = joystick.joy1_y2 * power;
	else
		motor[rightDrive] = 0;
}

void doLatch() { //DONT Migrate to joy1 for Dual Drivers
	if(joy1Btn(2))
		servo[latch] = LATCH_DOWN;
	else if(joy1Btn(4))
		servo[latch] = LATCH_UP;	//Upright
}

void outtake() {	//Migrate to joy1 for Dual Drivers
	if(joy1Btn(6))	//Right Bumper
		servo[hopper] = HOPPER_SCORE;
	else if(joy1Btn(8)) //Right Trigger
		servo[hopper] = HOPPER_LOAD;
}

int outtakeMode = 0;	//0: LOAD, 1: AIM, 2: SCORE
void outtakeSpecial() {
	if(joy1Btn(8))
		outtakeMode = 0;
	else if(joy1Btn(6)) {
		switch(outtakeMode) {
			case 0:
				outtakeMode = 1;
				wait1Msec(200);
				break;
			case 1:
				outtakeMode = 2;
				wait1Msec(200);
				break;
			case 2:
				outtakeMode = 0;
				wait1Msec(200);
				break;
			default:
				outtakeMode = 0;
		}
	}
	switch(outtakeMode) {
		case 0:
				servo[hopper] = HOPPER_LOAD;
				break;
		case 1:
			servo[hopper] = HOPPER_AIM;
			break;
		case 2:
			servo[hopper] = HOPPER_SCORE;
			break;
		default:
			outtakeMode = 0;
	}
}

void rollers() {	//Migrate to joy1 for Dual Drivers
	if(joy1Btn(1))
		motor[intakeRoller] = 96;
	else if(joy1Btn(3))
		motor[intakeRoller] = -96;
	else
		motor[intakeRoller] = 0;//Migrate to joy1 for Dual Drivers
}

void liftManual() {	//Migrate to joy1 for Dual Drivers
	if(joystick.joy1_TopHat == 0)
		motor[lift] = 128;
	else if(joystick.joy1_TopHat == 4)
		motor[lift] = -96;
	else if(joystick.joy1_TopHat == -1)
		motor[lift] = 0;
}

task main() {

  initializeRobot();

  waitForStart();

  while(true) {
  	getJoystickSettings(joystick);
  	drive(1);
  	doLatch();
  	outtakeSpecial();
  	rollers();
  	liftManual();
  }
}
