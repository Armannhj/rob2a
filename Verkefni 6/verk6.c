#pragma config(Sensor, in6,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in7,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in8,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  limitSwitch,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl12, armEncoder,     sensorQuadEncoder)
#pragma config(Motor,  port2,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, encoder, encoderPort, dgtl1, 1000)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed, encoder, encoderPort, dgtl3, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses 3 VEX Line Follower Sensors to track a black line on a light(er) surface.       *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 1     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 2     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 3     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
\*-----------------------------------------------------------------------------------------------4246-*/
#ifndef VERK6_H_
#define VERK6_H_

int checkButtonSequence()
{
    if (vexRT[Btn7L] && vexRT[Btn7D])
        return 1;
    return 0;
}

int basicMove(int speed) {

    motor[leftMotor] = speed;
    motor[rightMotor] = speed;

    return checkButtonSequence();
}

void wait(int milliseconds) {
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;

    wait1Msec(milliseconds);
}

void basicSwingTurn(int direction) {
    if (direction == -1) {
        motor[rightMotor] = 60;
        motor[leftMotor] = 20;
    }
    else {
        motor[rightMotor] = 20;
        motor[leftMotor] = 60;
    }
}

int followLine(int threshold)
{
    if (checkButtonSequence())
        return 1;

    //Turn right
    if (SensorValue[rightLineFollower] > threshold) {
        basicSwingTurn(1);
    }

    if (SensorValue[centerLineFollower] > threshold) {
        if (basicMove(60))
            return 1;
    }

    //Turn left
    if (SensorValue[leftLineFollower] > threshold) {
        basicSwingTurn(-1);
    }

    return 0;
}

void clawGrab()
{
		motor[clawMotor] = -80;
		wait1Msec(1000);
    while (SensorValue[limitSwitch] == 0)
        motor[armMotor] = -100;



    basicMove(50);
    wait1Msec(750);
  	wait(500);

    motor[clawMotor] = 127;
    wait1Msec(1000);
    motor[armMotor] = 0;

    motor[armMotor] = 60;
    wait1Msec(700);
    motor[armMotor] = 0;
}

void clawReset()
{
    motor[clawMotor] = 60;
    wait1Msec(500);
    motor[clawMotor] = 0;

    while (SensorValue[limitSwitch] == 0)
        motor[armMotor] = -100;
    motor[armMotor] = 0;

    motor[armMotor] = 127;
    wait1Msec(1000);
    motor[armMotor] = 0;
}

void turnAround()
{
    wait(500);
    motor[leftMotor] = 60;
    motor[rightMotor] = -60;
    wait1Msec(2000);

    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
}

#endif


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
