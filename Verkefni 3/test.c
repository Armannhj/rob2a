void driveForward(int forwardtime)
{
		while(SensorValue[leftEncoder] > forwardtime)  // While less than 5 rotations on the leftEncoder...
  	{
  			if(SensorValue[rightEncoder] == SensorValue[leftEncoder])
  			{
  				motor[rightMotor] = 60;
  				motor[leftMotor] = 60;
  			}
  			else if(SensorValue[rightEncoder] > SensorValue[leftEncoder])
  			{
  				motor[rightMotor] = 60;
  				motor[leftMotor] = 80;
  			}
  			else
  			{
  				motor[rightMotor] = 80;
  				motor[leftMotor] = 60;
  			}
  	}
}

void clearEncoder()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

void stopMotor()
{
	motor[rightMotor] = 0;
 	motor[leftMotor]  = 0;
 	wait1Msec(1000);  // 1 Second Delay
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
void leftTurn90()
{
	motor[leftMotor] = -60;
	motor[rightMotor]= 60;

	 while(SensorValue[rightEncoder] > -207 || SensorValue[leftEncoder] < 207)
	  {
    if(SensorValue[rightEncoder] > 207) {motor[rightMotor] = 0;}
    if(SensorValue[leftEncoder] < -207) {motor[leftMotor] = 0;}
    }
}


task drive()
{
			clearEncoder();

			driveForward(-564);

			stopMotor();

 			clearEncoder();

 			leftTurn90();

			stopMotor();

 			clearEncoder();

 			driveForward(-564);

 			stopMotor();

 			clearEncoder();

 			rightTurn90();

 			stopMotor();

 			clearEncoder();

 			driveForward(-564);

 			stopMotor();

 			clearEncoder();

 			rightTurn90();

 			stopMotor();

 			clearEncoder();

 			driveForward(-564);
}



task main()
{

StartTask(drive);
while(
){
StopAllTaskso
}

}
