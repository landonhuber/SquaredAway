#pragma config(Sensor, port10, speedLight,     sensorVexIQ_LED)
#pragma config(Motor,  motor4,          FrontClaw,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor5,          RightDrive,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor6,          Convayor,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         LeftDrive,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor12,         BackLock,      tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

string ConvayorDir = "off";
string speed = "fast";

void StartConvayor(){
	if (vexRT[BtnLUp] == 1) {
		if (ConvayorDir == "up"){
			stopMotor(Convayor);
			ConvayorDir = "off";
			} else {
			ConvayorDir = "up";
			setMotor(Convayor, 100);
		}

	}
	if (vexRT[BtnLDown] == 1) {
		if (ConvayorDir == "down"){
			stopMotor(Convayor);
			ConvayorDir = "off";
			} else {
			ConvayorDir = "down";
			setMotor(Convayor, -100);
		}
	}
	sleep(200);
}

void switchSpeed (){
	if (vexRT[BtnEUp] == 1){
		if (speed == "fast"){
			speed = "slow";
			setTouchLEDColor(speedLight, colorRed);
			}	else {
			speed = "fast";
			setTouchLEDColor(speedLight, colorGreen);
		}
	}
}

int driveSpeed(){
	int speedAmt = 1;
	if (speed == "fast"){
		speedAmt = 1;
		} else {
		speedAmt = 2;
	}
	return speedAmt;
}

void displayValues(){
	displayCenteredTextLine(0,"LeftMotor: %d", getMotorCurrent(LeftDrive));
	displayCenteredTextLine(1,"RightMotor: %d", getMotorCurrent(RightDrive));
	displayCenteredTextLine(2,"FrontClaw: %d", getMotorCurrent(FrontClaw));
	displayCenteredTextLine(3,"ConvayorMotor: %d", getMotorCurrent(Convayor));
	displayCenteredTextLine(4,"BackLockMotor: %d", getMotorCurrent(BackLock));
}
//short clawStop(){
//if(getBumperValue(ClawStopBtn) == 1) {
//	setMotorBrakeMode(FrontClaw, motorBrake);
//return BtnEDown;
//} else {
//setMotorBrakeMode(FrontClaw, motorHold);
//	return BtnRDown;
//}
//}

task main()
{
	speed = "fast";
	setTouchLEDColor(speedLight, colorGreen);
	setMotorCurrentLimit(BackLock, 300);
	repeat(forever){
		//displayValues();
		StartConvayor();
		switchSpeed();
		motor[RightDrive] = vexRT[ChD] / driveSpeed();
		motor[LeftDrive] = vexRT[ChA] / driveSpeed();
		armControl(FrontClaw, BtnRUp, BtnRDown, 100);
		armControl(BackLock,BtnFUp,BtnFDown,100);
	}
}
