PID chassisPIDValues;

void setChassis( int lPwr, int rPwr )
{

	motor[ fL ] = motor[ bL ] = lPwr;

	motor[ fR ] = motor[ bR ] = rPwr;

}

void chassisPID( int iStraight, int iTurn )
{

	int turn = 0;
	int straight = 0;

	if( straightPIDEnabled )
		straight = PIDCalc( chassisPIDValues, iStraight );
	if( turnPIDEnabled )
		turn = PIDCalc( gyroPIDValues, iTurn );

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
			chassisPID( ( SensorValue[ lEnc ] + SensorValue[ rEnc ] ) / 2, SensorValue[ gyro ] );
		if( liftPIDEnabled )
			setLift( PIDCalc( liftPIDValues, SensorValue[ liftPot ] ) );
		if( chainbarPIDEnabled )
			setChainbarSlew( PIDCalc( chainBarPIDValues, SensorValue[ chainbarEnc ] ));
		if( mogoPIDEnabled )
			setMogo( PIDCalc( mogoPIDValues, SensorValue[ mogoPot ] ) );

		wait1Msec( 20 );

	}

}
