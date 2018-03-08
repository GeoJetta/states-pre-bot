#define MOGO_DOWN_POS 1240
#define MOGO_UP_POS 3200

#define DOWN true
#define UP false

#define MOGO_SENSOR_THRESHOLD 2100

#define CHAINBAR_SCORE_POS 3000
#define CHAINBAR_LOADER_POS 2000
#define CHAINBAR_STAT_POS 1900
#define CHAINBAR_IDLE_UP_POS 1900
#define CHAINBAR_IDLE_DOWN_POS 1100
#define CHAINBAR_PICKUP_POS 980
#define CHAINBAR_HOLD_POWER isAbove( SensorValue[chainbarPot], 1350 )*15 ///*SensorValue[chainbarPot] < 1350 ? 15 : 1*/ 10.0 * cosDegrees( map( SensorValue[chainbarPot], 1400, 3000, 0, 90 ) )

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

void setIntake( int pwr, bool actuallySet = true )
{

	motor[ intake ] = pwr;

}

void mogoPosition( bool down, bool wait = false )
{

	if( SensorValue[ LIFT_SENSOR ] > LIFT_HORIZONTAL_POS )
	{

		liftPIDValues.target = LIFT_HORIZONTAL_POS;
		while( SensorValue[ LIFT_SENSOR ] > LIFT_HORIZONTAL_POS + 200 )
			wait1Msec( 20 );

	}

	if( down )
		mogoPIDValues.target = MOGO_DOWN_POS;
	else
		mogoPIDValues.target = MOGO_UP_POS;

	if( wait )
		waitForPID( mogoPIDValues );

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

void testDrop()
{

	liftPIDValues.target += 300;
	wait1Msec( 200 );
	setIntake( -127 );
	wait1Msec( 200 );
	liftPIDValues.target -= 500;
	wait1Msec( 100 );

}

void stack( );
void stackLoader(  );
void driverTestStack(  );

task stackTask
{

	driverTestStack(  );

}

task stackLoaderTask
{

	stackLoader(  );

}

int lastLiftPoint = 4000;

void liftToStack(  )
{

	int l1 = 0;
	int l2 = 0;
	int l3 = 0;
	int l4 = 0;
	int l5 = 0;
	int l6 = 0;

	float ultraAvg = (SensorValue[ stackDetect ]*2 + l1 + l2 + l3) / 5;

	liftPIDValues.target = LIFT_MAX_POS - 200;

	if( lastLiftPoint < LIFT_MIN_POS + 200 )
	{

		while( ultraAvg < 280 /*|| SensorValue[ LIFT_SENSOR ] > lastLiftPoint + 1200*/ )
		{

			wait1Msec( 50 );

			l6 = l5;
			l5 = l4;
			l4 = l3;
			l3 = l2;
			l2 = l1;
			l1 = SensorValue[ stackDetect ];

			ultraAvg = ( SensorValue[ stackDetect ]*2 + l1 + l2 + l3 + l4 + l5 ) / 7;

		}

	}
	else
	{

		while( SensorValue[ stackDetect ] < 280 )
		{
			wait1Msec( 50 );
		}

	}

	while( SensorValue[ liftPot ] > 2660 )
		wait1Msec( 20 );

	lastLiftPoint = SensorValue[ LIFT_SENSOR ];

	if( SensorValue[ liftPot ] < 1500 )
		chainbarPIDValues.target = CHAINBAR_SCORE_POS - 200;
	else
		chainbarPIDValues.target = CHAINBAR_SCORE_POS/* - 200*/;

	//TEST AND TUNE
	if( SensorValue[ liftPot ] < LIFT_MAX_POS + 100 )
		liftPIDValues.target = 	SensorValue[ LIFT_SENSOR ] + 100;
	else
		liftPIDValues.target = 	SensorValue[ LIFT_SENSOR ] - 50;
	//else if( SensorValue[ liftPot ] > 1500 )
	//	setLiftHeight( getLiftHeight() );
	//else if( SensorValue[ liftPot ] > 1000 )
	//	setLiftHeight( getLiftHeight() );
	//else
	//	setLiftHeight( getLiftHeight() + 2 );

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
		chainbarPIDValues.target = CHAINBAR_SCORE_POS;
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

void driverTestStack( )
{

	chainbarPIDEnabled = true;
	liftPIDEnabled = true;

	chainbarPIDValues.target = CHAINBAR_IDLE_DOWN_POS;
	liftToStack();

	if( false /*SensorValue[ liftPot ] > LIFT_MIN_POS - 300*/ )
		stack(  );
	else
	{

		if( SensorValue[ liftPot ] < LIFT_MAX_POS + 100 )
			while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 200 )
				wait1Msec( 20 );
		else
			while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 700 )
				wait1Msec( 20 );

		testDrop();

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

}

void autonStack( bool driving = false, bool last = false )
{

	chainbarPIDValues.target = CHAINBAR_IDLE_UP_POS;
	liftToStack();

	chainbarPIDValues.target = CHAINBAR_SCORE_POS - 200;
	while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 500 )
		wait1Msec( 20 );

	if( !driving )
		liftPIDValues.target += 200;
	else
		liftPIDValues.target += 400;
	if( SensorValue[ LIFT_SENSOR ] > 2100 )
		wait1Msec( 500 );
	else if( SensorValue[ LIFT_SENSOR ] > 1300 )
		wait1Msec( 400 );
	else
		wait1Msec( 100 );

	setIntake( -127 );
	liftPIDValues.target -= 500;
	wait1Msec( 350 );

	chainbarPIDValues.target = 400;
	while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
		wait1Msec( 20 );

	if( !last )
		liftPIDValues.target = LIFT_MIN_POS + 250;
	else
		liftPIDValues.target = LIFT_HORIZONTAL_POS - 400;

	wait1Msec( 500 );

	setIntake( 0 );
	if( !last )
		while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 150 )
			wait1Msec( 20 );

}

void thatOneCone()
{

	chainbarPIDValues.target = CHAINBAR_IDLE_UP_POS;
	liftPIDValues.target = 2400;
	while( SensorValue[ LIFT_SENSOR ] > 2500 )
		wait1Msec( 20 );

	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 100 )
		wait1Msec( 20 );

	liftPIDValues.target += 400;
	wait1Msec( 300 );

	setIntake( -127 );
	liftPIDValues.target -= 500;
	wait1Msec( 400 );

	chainbarPIDValues.target = 400;
	while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
		wait1Msec( 20 );

	setIntake( 0 );

	liftPIDValues.target = LIFT_MIN_POS + 250;

	while( SensorValue[ LIFT_SENSOR ] < LIFT_MIN_POS - 150 )
		wait1Msec( 20 );

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

		if( SensorValue[ liftPot ] > LIFT_MIN_POS - 300 )
		{


			chainbarPIDValues.target = CHAINBAR_SCORE_POS;
			while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 500 )
				wait1Msec( 20 );

			drop();

			chainbarPIDValues.target = CHAINBAR_LOADER_POS;
			while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
				wait1Msec( 20 );

			setIntake( 0 );

		}
		else
		{

			while( SensorValue[ chainbarPot ] < CHAINBAR_SCORE_POS - 700 )
				wait1Msec( 20 );

			testDrop();

			chainbarPIDValues.target = CHAINBAR_LOADER_POS;
			while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + 250 )
				wait1Msec( 20 );

			setIntake( 0 );

		}

		liftPIDValues.target = LIFT_LOADER_POS + 100;

		while( SensorValue[ LIFT_SENSOR ] < LIFT_LOADER_POS - 100 )
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

	if( vexRT[ Btn7UXmtr2 ] || vexRT[ Btn7DXmtr2 ] || vexRT[ Btn7LXmtr2 ] )
		lastLiftPoint = 4000;

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
				chainbarPIDValues.target = CHAINBAR_SCORE_POS;
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

enum stateControl
{

	MANUAL,
	STACKER,
	LOADER,
	LOADER_LINEUP,
	STAT

};

enum stateControl state = MANUAL;

void stateRun( enum stateControl lastState );

void stateSwitch()
{

	static enum stateControl lastState = MANUAL;

	lastState = state;

	bool liftButton = deadzone( vexRT[ Ch3Xmtr2 ] ) == 0 ? false : true;
	bool chainButton = deadzone( vexRT[ Ch2Xmtr2 ] ) == 0 ? false : true;

	if( chainButton || ( liftButton && state > MANUAL && state < STAT ) )
		state = MANUAL;
	else if( vexRT[ Btn8LXmtr2 ] )
		state = LOADER;
	else if( vexRT[ Btn8DXmtr2 ] )
		state = STACKER;
	else if( vexRT[ Btn8RXmtr2 ] )
		state = LOADER_LINEUP;
	else if( vexRT[ Btn8UXmtr2 ] )
		state = STAT;

	stateRun( lastState );

}

void stateRun( enum stateControl lastState )
{

	if( lastState != state )
	{

		if( lastState == LOADER )
			stopTask( stackLoaderTask );
		if( lastState == STACKER )
			stopTask( stackTask );

	}

	switch( state )
	{

		case MANUAL:

			liftPIDEnabled = false;
			chainbarPIDEnabled = false;

			setIntake( vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 + 15 );

			setChainbar( deadzone( vexRT[ Ch2Xmtr2 ] ) );
			setLift( deadzone( vexRT[ Ch3Xmtr2 ] ) );

		break;

		case STACKER:

			liftPIDEnabled = true;
			chainbarPIDEnabled = true;

			if( lastState != state )
				stackCurrent();

			if( vexRT[ Btn6DXmtr2 ] || vexRT[ Btn6UXmtr2 ] )
				setIntake( vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 );

		break;

		case LOADER:

			liftPIDEnabled = true;
			chainbarPIDEnabled = true;

			if( lastState != state )
				loadCurrent();

			if( vexRT[ Btn6DXmtr2 ] || vexRT[ Btn6UXmtr2 ] )
				setIntake( vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 );

		break;

		case LOADER_LINEUP:

			liftPIDEnabled = true;
			chainbarPIDEnabled = true;

			liftPIDValues.target = LIFT_LOADER_POS - 400;
  		chainbarPIDValues.target = CHAINBAR_LOADER_POS;

  		setIntake( vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 + 15 );

		break;

		case STAT:

			liftPIDEnabled = false;
			chainbarPIDEnabled = true;

			setLift( deadzone( vexRT[ Ch3Xmtr2 ] ) );
			setIntake( vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 + 15 );

			if( lastState != state )
				if( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS + ( -CHAINBAR_IDLE_UP_POS + CHAINBAR_SCORE_POS ) / 2 )
					toggled2.b8U = false;
				else
					toggled2.b8U = true;

			if( toggled2.b8U )
				chainbarPIDValues.target = CHAINBAR_SCORE_POS;
			else
				chainbarPIDValues.target = CHAINBAR_STAT_POS;

		break;

	}

}
