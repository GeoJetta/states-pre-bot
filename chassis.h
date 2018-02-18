#define CHASSIS_TICKS_PER_INCH 999999

PID distancePIDValues;
PID turnPIDValues;
PID gyroPIDValues;
PID chainBarPIDValues;
PID mogoPIDValues;

void setChassis( int lPwr, int rPwr )
{

	motor[ fL ] = motor[ bL ] = lPwr;

	motor[ fR ] = motor[ bR ] = rPwr;

}

bool distancePIDEnabled = false;
bool turnPIDEnabled = false;

void chassisPID(  )
{

	int turn = 0;
	int straight = 0;

	if( distancePIDEnabled )
		straight = PIDCalc( distancePIDValues );
	if( turnPIDEnabled )
		turn = PIDCalc( gyroPIDValues );

	setChassis( straight + turn, straight - turn );

}

bool chassisPIDEnabled = false;
bool liftPIDEnabled = false;
bool chainbarPIDEnabled = false;
bool mogoPIDEnabled = false;

task PIDLoop
{

	while( true )
	{

		if( chassisPIDEnabled )
			chassisPID( );

		if( liftPIDEnabled )
			setLift( PIDCalc( liftPIDValues ) );

		if( chainbarPIDEnabled )
			setChainbar( PIDCalc( chainBarPIDValues ) );

		if( mogoPIDEnabled )
			setMogo( PIDCalc( mogoPIDValues ) );

		wait1Msec( 20 );

	}

}

float getDistance(  )
{

	return SensorValue[ CHASSIS_DISTANCE_SENSOR ] * CHASSIS_TICKS_PER_INCH;

}

void setDriveTarget( float iInches )
{

	distancePIDValues.target = CHASSIS_TICKS_PER_INCH * iInches;

}

void moveDriveTarget( float iInches )
{

	distancePIDValues.target += CHASSIS_TICKS_PER_INCH * iInches;

}

void mogoPickup( bool waitToDrive = false )
{

	mogoPIDValues.target = MOGO_DOWN_POS;

	if( waitToDrive )
		waitForPID( mogoPIDValues );

	moveDriveTarget( 144 );

	while( !SensorValue[ mogoTouch ] )
		wait1Msec( 20 );

	mogoPIDValues.target = MOGO_UP_POS;
	while( !mogoPIDValues.complete )
	{
		//TEST THIS
		setDriveTarget( getDistance() + ( MOGO_UP_POS - SensorValue[ mogoPot ] ) / 1000 );
		wait1Msec( 20 );
	}

}

//Typed in GitHub - test in RobotC
void driveArc( float radius, float degrees )
{
	
	startDist = getDistance();
	startAngle = SensorValue[ gyro ];
	
	circumference = 2*PI * radius;
	arcLength = circumference * ( degrees / 360 );
	moveDriveTarget( arcLength );
	while( !distancePIDValues.complete )
	{
		
		turnPIDValues.target = map( getDistance(), startDist, startDist + arcLength, startAngle, startAngle + degrees );
		wait1MSec( 50 );
		
	}
}
