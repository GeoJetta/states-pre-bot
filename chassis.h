#define CHASSIS_TICKS_PER_INCH 28.426

PID distancePIDValues;
PID gyroPIDValues;

void setChassis( int lPwr, int rPwr )
{

	motor[ frontLeftChassis ]		=
	motor[ backLeftChassis ] 		= lPwr;

	motor[ frontRightChassis ]	=
	motor[ backRightChassis ] 	= rPwr;

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

	setChassis( straight - turn, straight + turn );

}

bool chassisPIDEnabled = false;

task PIDLoop
{

	while( true )
	{

		if( chassisPIDEnabled )
			chassisPID( );

		if( liftPIDEnabled )
			setLift( PIDCalc( liftPIDValues ) );

		if( chainbarPIDEnabled )
			setChainbar( PIDCalc( chainbarPIDValues ) + CHAINBAR_HOLD_POWER);

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

	//TODO: Add back in once we have the sensor mounted
	//while( !SensorValue[ mogoTouch ] )
		wait1Msec( 20 );

	mogoPIDValues.target = MOGO_UP_POS;
	while( !mogoPIDValues.complete )
	{
		//TEST THIS
		setDriveTarget( getDistance() + ( MOGO_UP_POS - SensorValue[ mogoPot ] ) / 1000 );
		wait1Msec( 20 );

	}

}

void driveArc( float radius, float degrees )
{

	float startDist = getDistance();
	float startAngle = SensorValue[ gyro ] / 10;

	float circumference = 2.00*PI * radius;
	float arcLength = circumference * ( degrees / 360.00 );

	moveDriveTarget( arcLength );
	while( !distancePIDValues.complete )
	{

		gyroPIDValues.target = 10* map( getDistance(), startDist, startDist + arcLength, startAngle, startAngle + degrees );
		wait1Msec( 50 );

	}

}
