PID liftPIDValues;

#define FOUR_BAR_LENGTH 14.0
#define TOWER_HEIGHT 17.0
#define SECONDARY_TOWER_HEIGHT 11.0
#define LIFT_HORIZONTAL_POS 2000
#define LIFT_MIN_POS 2690 //TODO
#define LIFT_MAX_POS 910 //TODO
#define LIFT_MIN_DEG 0 //TODO - integrate into height map (might not be 250 degrees exactly)
#define LIFT_MAX_DEG 90 //TODO
#define LIFT_HORIZONTAL_DEG map( LIFT_HORIZONTAL_POS, 4095, 0, 0, 250 )
#define LIFT_MAX_HEIGHT 40 //TODO
#define LIFT_MIN_HEIGHT 9.0
#define LIFT_LOADER_POS 2730

#define LIFT_SENSOR liftPot

#define ULTRASONIC_BASELINE 368 //TODO

void setLift( int pwr )
{

	motor[ lLift ] = pwr;
	motor[ rLift ] = pwr;

}

float getLiftHeight(  )
{

	//Change horizontal degrees to a calculated constant?
	float theta = map( SensorValue( LIFT_SENSOR ), 4095, 0, 0, 250 ) - LIFT_HORIZONTAL_DEG;

	return TOWER_HEIGHT + SECONDARY_TOWER_HEIGHT + 2 * FOUR_BAR_LENGTH * sinDegrees( theta );

}

void setLiftHeight( float iInches )
{

	float theta;

	if( iInches > 27 )
		theta =	radiansToDegrees( asin( ( ( iInches - TOWER_HEIGHT - SECONDARY_TOWER_HEIGHT )*0.5 ) /
								(float)FOUR_BAR_LENGTH ) );
	else
		theta =	-radiansToDegrees( asin( ( ( 27 - iInches - TOWER_HEIGHT - SECONDARY_TOWER_HEIGHT )*0.5 ) /
								(float)FOUR_BAR_LENGTH ) );

	liftPIDValues.target = map( theta, 0, 250, 4095, 0 ) - LIFT_HORIZONTAL_POS;

}



void liftToStackLoop(  )
{

	bool wasHit = false;
	int hitVal = 0;

	if( fabs( ULTRASONIC_BASELINE - SensorValue[ stackDetect ] ) > 50 )
	{

		wasHit = false;
		liftPIDValues.target = LIFT_MAX_POS;

	}
	else
	{

		if( !wasHit )
			hitVal = SensorValue[ LIFT_SENSOR ];
		//TEST AND TUNE
		liftPIDValues.target = hitVal;
		wasHit = true;

	}

}
