#define CHASSIS_TICKS_PER_INCH 999999

PID distancePIDValues;
PID turnPIDValues;
PID gyroPIDValues;
PID liftPIDValues;
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

void setDriveTarget( int iInches )
{

	distancePIDValues.target = CHASSIS_TICKS_PER_INCH * iInches;

}

void moveDriveTarget( int iInches )
{

	distancePIDValues.target += CHASSIS_TICKS_PER_INCH * iInches;

}
