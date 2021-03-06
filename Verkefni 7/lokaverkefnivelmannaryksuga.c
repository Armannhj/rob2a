#pragma config(Sensor, in6,    ,               sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorNone)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl12, armEncoder,     sensorQuadEncoder)
#pragma config(Motor,  port2,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, encoder, encoderPort, dgtl1, 1000)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed, encoder, encoderPort, dgtl3, 1000)
//*              !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                                                    *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses the Ultrasonic sensor to detect objects, and maintain a desired distance from   *|
|*  that object.  However, with standart VEX motors, you may find it difficult to slowly creep up to  *|
|*  the object as the motors will not have enough power to move the robot.                            *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  The Sonar Sensor should be somewhere on the FRONT of the robot, facing FORWARD.             *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Digital 5               sonarSensor         VEX Sonar Sensor    Front mounted, front facing     *|
|*    Motor - Port 2          leftMotor           VEX Motor           Left motor                      *|
|*    Motor - Port 3          rightMotor          VEX Motor           Right motor                     *|
\*-----------------------------------------------------------------------------------------------4246-*/

void stopMotor()
{
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	wait1Msec(500);
}

void clearEncoder()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

void rightTurn90()
{
	motor[leftMotor] = 60;
	motor[rightMotor]= -60;

	 while(SensorValue[rightEncoder] < 207 || SensorValue[leftEncoder] > -207)
	 {
    if(SensorValue[rightEncoder] > 207) {motor[rightMotor] = 0;}
    if(SensorValue[leftEncoder] < -207) {motor[leftMotor] = 0;}
   }
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
 	int run = 1;
 	while(run == 1)
	{
		if(vexRT[Btn8D] == 1)
		{
			int rundrive = 1;
			while(rundrive == 1)
			{


				while(SensorValue(sonarSensor) > 15 || SensorValue(sonarSensor) == -1)
				{
					motor[rightMotor] = 63;
					motor[leftMotor] = 63;

					if(vexRT[Btn8U] == 1)
					{
						StopAllTasks();
						stopMotor();
						rundrive = 0;
					}
				}
				while(SensorValue(sonarSensor) < 15)
				{
					clearEncoder();
					rightTurn90();

					if(SensorValue(sonarSensor) > 15 || SensorValue(sonarSensor) == -1)
					{
						break;
					}

					if(vexRT[Btn8U] == 1)
					{
						StopAllTasks();
						stopMotor();
						rundrive = 0;
					}
				}


			}
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
