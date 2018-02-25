#define MOGO_DOWN_POS 1200
#define MOGO_UP_POS 3240

#define CHAINBAR_SCORE_POS 3000
#define CHAINBAR_LOADER_POS 2000
#define CHAINBAR_STAT_POS 1900
#define CHAINBAR_IDLE_UP_POS 1900
#define CHAINBAR_IDLE_DOWN_POS 1100
#define CHAINBAR_PICKUP_POS 980
#define CHAINBAR_HOLD_POWER 25.0 * cosDegrees( map( SensorValue[chainbarPot], 1400, 3000, 0, 90 ) )

PID chainbarPIDValues;
PID mogoPIDValues;

bool liftPIDEnabled = false;
bool chainbarPIDEnabled = false;
bool mogoPIDEnabled = false;

void setMogo( int pwr )
{

	motor[ mogo ] = pwr;

}

void setChainbar( int pwr )
{

	motor[ lChainbar ] = pwr;
	motor[ rChainbar ] = pwr;

}

void setIntake( int pwr )
{

	motor[ intake ] = pwr;

}

void drop()
{

	liftPIDValues.target += 200;
	if( SensorValue[ LIFT_SENSOR ] > 2100 )
		wait1Msec( 500 );
	else if( SensorValue[ LIFT_SENSOR ] > 1300 )
		wait1Msec( 400 );
	else
		wait1Msec( 100 );

	if( SensorValue[ liftPot ] < 1300 )
		wait1Msec( 400 );

	setIntake( -127 );
	//wait1Msec( 200 );
	liftPIDValues.target -= 300;
	wait1Msec( 200 );

}

void stack( );
void stackLoader(  );

task stackTask
{

	stack(  );

}

task stackLoaderTask
{

	stackLoader(  );

}

bool stacking = false;
void stack( )
{

	chainbarPIDEnabled = true;
	liftPIDEnabled = true;

	chainbarPIDValues.target = CHAINBAR_IDLE_UP_POS;
	liftToStack();

	//waitForPID( liftPIDValues );
	if( SensorValue[ LIFT_SENSOR ] > 1400 )
		chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	else
		chainbarPIDValues.target = CHAINBAR_SCORE_POS + 250;
	while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 500 )
		wait1Msec( 20 );

	drop();

	chainbarPIDValues.target = CHAINBAR_IDLE_DOWN_POS;
	while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
		wait1Msec( 20 );

	setIntake( 0 );

	liftPIDValues.target = LIFT_MIN_POS;
	toggled2.b8D = false;

	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS )
		wait1Msec( 20 );

	liftPIDEnabled = false;
	chainbarPIDEnabled = false;
	stacking = false;

	stopTask( stackTask );

}

void stackLoader(  )
{

	bool maxed = false;

	while( true )
	{

		chainbarPIDEnabled = true;
		liftPIDEnabled = true;

		chainbarPIDValues.target = CHAINBAR_IDLE_UP_POS;
		liftToStack();

		if( SensorValue[ LIFT_SENSOR ] < 1420 )
			maxed = true;

		if( SensorValue[ LIFT_SENSOR ] > 1400 )
			chainbarPIDValues.target = CHAINBAR_SCORE_POS;
		else
			chainbarPIDValues.target = CHAINBAR_SCORE_POS + 250;
		while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 500 )
			wait1Msec( 20 );

		drop();

		chainbarPIDValues.target = CHAINBAR_LOADER_POS;
		while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
			wait1Msec( 20 );

		setIntake( 0 );

		liftPIDValues.target = LIFT_LOADER_POS;

		while( SensorValue[ LIFT_SENSOR ] < LIFT_LOADER_POS - 200 )
			wait1Msec( 20 );

		setIntake( 127 );
		wait1Msec( 200 );
		setIntake( 15 );

	}

}

void stackCurrent(  )
{

	startTask( stackTask );

}

void loadCurrent(  )
{

	startTask( stackLoaderTask );

}

bool loading = false;
bool presetOn = false;
void driverLift(  )
{

	if( vexRT[ Btn6UXmtr2 ] || vexRT[ Btn6DXmtr2 ] )
		motor[ intake ] = vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127;

	if( SensorValue[ mogoPot ] < MOGO_DOWN_POS + 200 )
		motor[ mogo ] = vexRT[ Btn7UXmtr2 ] * 147 - vexRT[ Btn7DXmtr2 ] * 127 - 20;
	else
		motor[ mogo ] = vexRT[ Btn7UXmtr2 ] * 127 - vexRT[ Btn7DXmtr2 ] * 127;

	if( toggled2.b8R )
		presetOn = false;
	if( pressed2.b8U )
	{

		presetOn = true;
		toggled2.b8R = false;

	}

	if( !presetOn )
		if( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + ( -CHAINBAR_IDLE_UP_POS + CHAINBAR_SCORE_POS ) / 2 )
			toggled2.b8U = false;
		else
			toggled2.b8U = true;

	if( deadzone( vexRT[ Ch3Xmtr2 ] ) != 0 && deadzone( vexRT[ Ch2Xmtr2 ] ) != 0 &&
  					!( deadzone( vexRT[ Ch2Xmtr2 ] ) < 0 && SensorValue[ chainbarPot ] < CHAINBAR_PICKUP_POS ))
  {

  	toggled2.b8D = false;
  	toggled2.b8L = false;
  	toggled2.b8R = false;
  	stacking = false;
  	loading = false;
  	stopTask( stackTask );
  	stopTask( stackLoaderTask );
		liftPIDEnabled = false;
  	setLift( vexRT[ Ch3Xmtr2 ] );

		chainbarPIDEnabled = false;
		presetOn = false;
		setChainbar( vexRT[ Ch2Xmtr2 ] );

  }
  else if( deadzone( vexRT[ Ch3Xmtr2 ] ) != 0 )
  {

  	toggled2.b8D = false;
  	toggled2.b8L = false;
  	toggled2.b8R = false;
  	stacking = false;
  	loading = false;
  	stopTask( stackTask );
  	stopTask( stackLoaderTask );
  	chainbarPIDEnabled = false;
		liftPIDEnabled = false;
  	setLift( vexRT[ Ch3Xmtr2 ] );

  }
  else if( 	deadzone( vexRT[ Ch2Xmtr2 ] ) != 0 &&
  					!( deadzone( vexRT[ Ch2Xmtr2 ] ) < 0 && SensorValue[ chainbarPot ] < CHAINBAR_PICKUP_POS ) )
  {

  	toggled2.b8D = false;
  	toggled2.b8L = false;
  	toggled2.b8R = false;
  	stacking = false;
  	loading = false;
  	stopTask( stackTask );
  	stopTask( stackLoaderTask );
  	chainbarPIDEnabled = false;
		liftPIDEnabled = false;
  	setChainbar( vexRT[ Ch2Xmtr2 ] );
  	presetOn = false;

  }
  else if( toggled2.b8D && !stacking )
  {

  	stackCurrent();
  	stacking = true;

  }
  else if( toggled2.b8L && !loading )
  {

  	loadCurrent();
  	loading = true;

  }
 	else if( !stacking && !loading && ( vexRT[ Btn6UXmtr2 ] || vexRT[ Btn6DXmtr2 ] ) )
 	{

 		setLift( 0 );
 		if( !presetOn && !toggled2.b8R )
  		setChainbar( CHAINBAR_HOLD_POWER );

 	}
 	else if( !stacking && !loading )
 	{

 		setLift( 0 );
 		if( !presetOn && !toggled2.b8R )
  		setChainbar( CHAINBAR_HOLD_POWER );
 		setIntake( 15 );

 	}

  if( deadzone( vexRT[ Ch2Xmtr2 ] ) == 0 && !stacking && !loading && presetOn )
  {

  	chainbarPIDEnabled = true;
  	if( toggled2.b8U )
  		if( SensorValue[ LIFT_SENSOR ] > 1400 )
				chainbarPIDValues.target = CHAINBAR_SCORE_POS;
			else
				chainbarPIDValues.target = CHAINBAR_SCORE_POS + 250;
  	else
  		chainbarPIDValues.target = CHAINBAR_STAT_POS;

 	}
 	else if( deadzone( vexRT[ Ch3Xmtr2 ] ) == 0 && deadzone( vexRT[ Ch2Xmtr2 ] ) == 0 && !stacking && !loading && toggled2.b8R )
  {

  	chainbarPIDEnabled = true;
  	liftPIDEnabled = true;
  	liftPIDValues.target = LIFT_LOADER_POS - 400;
  	chainbarPIDValues.target = CHAINBAR_LOADER_POS;

 	}

}
