
void redTwentyLeft(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	moveTurnTarget( CLOCKWISE, 10, false );
	wait1Msec( 200 );
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	waitForPID( liftPIDValues );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		while( SensorValue[ chainbarPot ] > 700 )
			wait1Msec( 20 );
		wait1Msec( 400 );
		setIntake( 30 );
		moveDriveTarget( 12, false );
		thatOneCone();

		setIntake( 127 );
		wait1Msec( 500 );
		setIntake( 15 );
		setDriveTarget( 0, false );
		autonStack( true );

	}

	waitForPID( distancePIDValues );
	setTurnTarget( 35, COUNTER_CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	moveDriveTarget( -18, false );
	wait1Msec( 100 );
	waitForPID( distancePIDValues );
	moveTurnTarget( 100, COUNTER_CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	liftPIDValues.target = LIFT_HORIZONTAL_POS - 400;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	chassisPIDEnabled = false;
	setChassis( 127, 127 );
	wait1Msec( 450 );
	mogoPIDValues.target = 1800;
	wait1Msec( 1200 );
	setChassis( -127, -127 );
	wait1Msec( 800 );
	setChassis( 0, 0 );

}

void redFiveLeft(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	//setIntake( 127 );
	//wait1Msec( 200 );
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 300 )
		wait1Msec( 20 );
	wait1Msec( 400 );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		waitForPID( chainbarPIDValues );
		setIntake( 30 );
		moveDriveTarget( 10, false );
		thatOneCone();

		setIntake( 127 );
		wait1Msec( 500 );
		setIntake( 15 );
		if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2230 )
		{

			autonStack( true );
			setIntake( 127 );
			moveDriveTarget( 8, false );
			wait1Msec( 400 );
			liftPIDValues.target = LIFT_MIN_POS + 200;
			chainbarPIDValues.target = 400;
			wait1Msec( 900 );
			moveDriveTarget( -9, false );
			setIntake( 15 );

		}

		setDriveTarget( 2, false );
		autonStack( true );

	}
	else
		setDriveTarget( 2, false );

	liftPIDValues.target = LIFT_HORIZONTAL_POS - 200;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;

	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > 150 )
		wait1Msec( 20 );
	setTurnTarget( 100, COUNTER_CLOCKWISE, false );
	wait1Msec( 100 );
	while( SensorValue[ gyro ] < 700 )
		wait1Msec( 20 );
	moveDriveTarget( -4, false );
	mogoPIDValues.target = MOGO_DOWN_POS;
	while( SensorValue[ mogoPot ] > MOGO_DOWN_POS + 1000 )
		wait1Msec( 20 );
	moveDriveTarget( -24, false );
	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > -200 )
		wait1Msec( 20 );
}

void blueTwentyRight(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	moveTurnTarget( COUNTER_CLOCKWISE, 10, false );
	wait1Msec( 200 );
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	waitForPID( liftPIDValues );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		while( SensorValue[ chainbarPot ] > 700 )
			wait1Msec( 20 );
		wait1Msec( 400 );
		setIntake( 30 );
		moveDriveTarget( 12, false );
		thatOneCone();

		setIntake( 127 );
		wait1Msec( 500 );
		setIntake( 15 );
		setDriveTarget( 0, false );
		autonStack( true );

	}

	waitForPID( distancePIDValues );
	setTurnTarget( 35, CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	moveDriveTarget( -18, false );
	wait1Msec( 100 );
	waitForPID( distancePIDValues );
	moveTurnTarget( 100, CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	liftPIDValues.target = LIFT_HORIZONTAL_POS - 400;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	chassisPIDEnabled = false;
	setChassis( 127, 127 );
	wait1Msec( 450 );
	mogoPIDValues.target = 1800;
	wait1Msec( 1200 );
	setChassis( -127, -127 );
	wait1Msec( 800 );
	setChassis( 0, 0 );

}

void blueFiveRight(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	//setIntake( 127 );
	//wait1Msec( 200 );
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 300 )
		wait1Msec( 20 );
	wait1Msec( 400 );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		waitForPID( chainbarPIDValues );
		setIntake( 30 );
		distancePIDValues.target = 2050;
		thatOneCone();

		setIntake( 127 );
		wait1Msec( 500 );
		setIntake( 15 );
		if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2230 )
		{

			autonStack( true );
			setIntake( 127 );
			distancePIDValues.target = 2300;
			wait1Msec( 400 );
			liftPIDValues.target = LIFT_MIN_POS + 200;
			chainbarPIDValues.target = 400;
			wait1Msec( 900 );
			moveDriveTarget( -9, false );
			setIntake( 15 );

		}

		setDriveTarget( 8, false );
		autonStack( true );

	}
	else
		setDriveTarget( 8, false );

	liftPIDValues.target = LIFT_HORIZONTAL_POS - 200;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;

	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > distancePIDValues.target + 2*CHASSIS_TICKS_PER_INCH )
		wait1Msec( 20 );
	setTurnTarget( 129, CLOCKWISE, false );
	wait1Msec( 100 );
	while( SensorValue[ gyro ] > -700 )
		wait1Msec( 20 );
	moveDriveTarget( 2, false );
	mogoPIDValues.target = MOGO_DOWN_POS;
	while( SensorValue[ mogoPot ] > MOGO_DOWN_POS + 1000 )
		wait1Msec( 20 );
	moveDriveTarget( -24, false );
	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > -200 )
		wait1Msec( 20 );
}

void blueFiveRightStat(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 300 )
		wait1Msec( 20 );
	wait1Msec( 400 );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );
	moveDriveTarget( 6, false );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		waitForPID( chainbarPIDValues );
		setIntake( 30 );
		setDriveTarget( 8, false );
		chainbarPIDValues.target = CHAINBAR_IDLE_DOWN_POS;

	}
	else
		setDriveTarget( 8, false );

	liftPIDValues.target = LIFT_HORIZONTAL_POS - 200;

	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > distancePIDValues.target + 2*CHASSIS_TICKS_PER_INCH )
		wait1Msec( 20 );
	distancePIDEnabled = false;
	sDistancePIDEnabled = true;
	sDistancePIDValues.stuck = false;
	sDistancePIDValues.stopped = false;
	sDistancePIDValues.startStoppedTime = nPgmTime;
	sDistancePIDValues.targetChangedTime = nPgmTime;
	sDistancePIDValues.target = distancePIDValues.target;
	waitForPID( sDistancePIDValues );
	setTurnTarget( 129, CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	mogoPIDValues.target = MOGO_DOWN_POS;
	while( SensorValue[ mogoPot ] > MOGO_DOWN_POS + 1000 )
		wait1Msec( 20 );
	distancePIDEnabled = true;
	sDistancePIDEnabled = false;
	distancePIDValues.target -= 18 * CHASSIS_TICKS_PER_INCH;
	wait1Msec( 100 );
	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] > distancePIDValues.target + 2*CHASSIS_TICKS_PER_INCH )
		wait1Msec( 20 );
	distancePIDEnabled = false;
	sDistancePIDEnabled = true;
	sDistancePIDValues.stuck = false;
	sDistancePIDValues.stopped = false;
	sDistancePIDValues.startStoppedTime = nPgmTime;
	sDistancePIDValues.targetChangedTime = nPgmTime;
	sDistancePIDValues.target = distancePIDValues.target;
	waitForPID( sDistancePIDValues );
	distancePIDEnabled = true;
	sDistancePIDEnabled = false;
	moveTurnTarget( 86.2, CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );

	chainbarPIDValues.target = 122;
	liftPIDValues.target = 1500;

	distancePIDValues.target += 18 * CHASSIS_TICKS_PER_INCH;
	wait1Msec( 100 );
	while( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < distancePIDValues.target - 4*CHASSIS_TICKS_PER_INCH )
		wait1Msec( 20 );
	wait1Msec( 200 );

	liftPIDValues.target = 1600;
	wait1Msec( 200 );

	setIntake( -127 );

	moveDriveTarget( -18, true );
	moveTurnTarget( COUNTER_CLOCKWISE, 80, true );
	moveDriveTarget( -24, true );

}


void blueTwentyRightOld(  )
{

	liftPIDEnabled = true;
	chainbarPIDEnabled = true;
	chassisPIDEnabled = true;
	mogoPIDEnabled = true;
	distancePIDEnabled = true;
	turnPIDEnabled = true;
	liftPIDValues.target = SensorValue[ LIFT_SENSOR ];
	chainbarPIDValues.target = SensorValue[ chainbarPot ];
	mogoPIDValues.target = SensorValue[ mogoPot ];
	//setIntake( 127 );
	//wait1Msec( 200 );
	setIntake( 30 );
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	mogoPickup();
	liftPIDValues.target = LIFT_MIN_POS;
	distancePIDValues.target = 1700;
	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 300 )
		wait1Msec( 20 );
	setIntake( -127 );
	wait1Msec( 200 );
	setIntake( 0 );

	if( SensorValue[ CHASSIS_DISTANCE_SENSOR ] < 2050 )
	{

		chainbarPIDValues.target = 400;
		setIntake( 127 );
		waitForPID( chainbarPIDValues );
		setIntake( 30 );
		moveDriveTarget( 10, false );
		thatOneCone();

		setIntake( 127 );
		wait1Msec( 500 );
		setIntake( 15 );

		setDriveTarget( 0, false );
		autonStack( true );

	}
	else
		setDriveTarget( 0, false );

	liftPIDValues.target = LIFT_HORIZONTAL_POS - 200;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;

	waitForPID( distancePIDValues );
	setTurnTarget( 35, CLOCKWISE, false );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	moveDriveTarget( -24, true );
	wait1Msec( 100 );
	waitForPID( distancePIDValues );
	moveTurnTarget( 100, CLOCKWISE, true );
	wait1Msec( 100 );
	waitForPID( gyroPIDValues );
	liftPIDValues.target = LIFT_HORIZONTAL_POS;
	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	moveDriveTarget( 50, false );
	wait1Msec( 500 );
	mogoPIDValues.target = 1650;
	wait1Msec( 700 );
	moveDriveTarget( -50 );

}
