PID liftPIDValues;

#define FOUR_BAR_LENGTH 10.0
#define TOWER_HEIGHT 10.0
#define SECONDARY_TOWER_HEIGHT 5.0
#define LIFT_HORIZONTAL_POS 1000
#define LIFT_HORIZONTAL_DEG map( LIFT_HORIZONTAL_POS, 0, 4095, 0, 250 )
#define LIFT_MAX_HEIGHT 40

#define LIFT_SENSOR SensorValue[ liftPot ]

#define ULTRASONIC_BASELINE 100

void setLift( int pwr )
{

	motor[lLift] = pwr;
	motor[rLift] = pwr;

}

float getLiftHeight(  )
{

	//Change horizontal degrees to a calculated constant?
	float theta = map( LIFT_SENSOR, 0, 4095, 0, 250 ) - LIFT_HORIZONTAL_DEG;

	return TOWER_HEIGHT + SECONDARY_TOWER_HEIGHT + 2 * FOUR_BAR_LENGTH * sinDegrees( theta );

}

void setLiftHeight( float iInches )
{

	float theta = radiansToDegrees( asin( ( iInches - TOWER_HEIGHT - SECONDARY_TOWER_HEIGHT ) / (float)FOUR_BAR_LENGTH ) );

	liftPIDValues.target = map( theta, 0, 250, 0, 4095 ) + LIFT_HORIZONTAL_DEG;

}

void liftToStack(  )
{

	setLiftHeight( LIFT_MAX_HEIGHT );

	while( fabs( ULTRASONIC_BASELINE - SensorValue[ stackDetect ] ) > 5 )
		wait1Msec( 20 );

	//TEST AND TUNE
	liftPIDValues.target = LIFT_SENSOR + liftPIDValues.deltaPV;

}
