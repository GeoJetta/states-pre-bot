#define CHASSIS_TICKS_PER_INCH 28.426
#define CLOCKWISE true
#define COUNTER_CLOCKWISE false

PID distancePIDValues;
PID sDistancePIDValues;
PID gyroPIDValues;

void setChassis( int lPwr, int rPwr )
{

	motor[ frontLeftChassis ]		=
	motor[ backLeftChassis ] 		= lPwr;

	motor[ frontRightChassis ]	=
	motor[ backRightChassis ] 	= rPwr;

}

bool distancePIDEnabled = false;
bool sDistancePIDEnabled = false;
bool turnPIDEnabled = false;

void chassisPID(  )
{

	int turn = 0;
	int straight = 0;

	if( distancePIDEnabled )
		straight = PIDCalc( distancePIDValues );
	else if( sDistancePIDEnabled )
		straight = PIDCalc( sDistancePIDValues );
	if( turnPIDEnabled )
		turn = PIDCalc( gyroPIDValues );

	if( abs( straight ) + abs( turn ) > 127 )
	{

		capVal( turn, 20 );
		capVal( straight, 100 );

	}

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

void setDriveTarget( float iInches, bool wait = false )
{

	distancePIDValues.target = CHASSIS_TICKS_PER_INCH * iInches;
	if( wait )
		waitForPID( distancePIDValues );

}

void moveDriveTarget( float iInches, bool wait = false )
{

	distancePIDValues.target += CHASSIS_TICKS_PER_INCH * iInches;
	if( wait )
		waitForPID( distancePIDValues );

}

void setTurnTarget( float degrees, bool clockwise, bool wait = false )
{

	if( clockwise )
		degrees = -degrees;

	gyroPIDValues.target = degrees*10.0;
	if( wait )
		waitForPID( gyroPIDValues );

}

void moveTurnTarget( float degrees, bool clockwise, bool wait = false )
{

	if( clockwise )
		degrees = -degrees;

	gyroPIDValues.target += degrees*10.0;
	if( wait )
		waitForPID( gyroPIDValues );

}

void mogoPickup( bool waitToDrive = false )
{

	mogoPosition( DOWN, waitToDrive );

	moveDriveTarget( 84 );

	while( SensorValue[ mogoSense ] > MOGO_SENSOR_THRESHOLD )
		wait1Msec( 20 );

	mogoPIDValues.target = MOGO_UP_POS;
	distancePIDValues.target = 	SensorValue[ CHASSIS_DISTANCE_SENSOR ];
	while( SensorValue[ mogoPot ] < MOGO_UP_POS - 400 )
	{
		//TEST THIS
		distancePIDValues.target = 	SensorValue[ CHASSIS_DISTANCE_SENSOR ] +
																( MOGO_UP_POS - SensorValue[ mogoPot ] ) / 40.0;
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

		gyroPIDValues.target = 10* map( getDistance(),
			startDist, startDist + arcLength, startAngle, startAngle + degrees );
		wait1Msec( 50 );

	}

}
