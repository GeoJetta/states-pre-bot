#define MOGO_DOWN_POS 1200
#define MOGO_UP_POS 3240

#define CHAINBAR_SCORE_POS 3000
#define CHAINBAR_IDLE_UP_POS 1700
#define CHAINBAR_IDLE_DOWN_POS 1400
#define CHAINBAR_PICKUP_POS 980

PID chainbarPIDValues;
PID mogoPIDValues;

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

	setIntake( -127 );
	wait1Msec( 500 );
	setIntake( 0 );

}

int cones = 1;

void stack( int iCones );

task liftTask
{

	stack( cones );

}

void stack( int iCones )
{

	chainbarPIDValues.target = CHAINBAR_IDLE_UP_POS;
	setLiftHeight( LIFT_MIN_HEIGHT + iCones * 4 ); //TODO (tune val)
	waitForPID( liftPIDValues );

	chainbarPIDValues.target = CHAINBAR_SCORE_POS;
	waitForPID( chainbarPIDValues );

	drop();

	chainbarPIDValues.target = CHAINBAR_IDLE_DOWN_POS;
	while( SensorValue[ chainbarPot ] > CHAINBAR_IDLE_UP_POS )
		wait1Msec( 20 );
	setLiftHeight( LIFT_MIN_HEIGHT );

	stopTask( liftTask );

}

void stackCurrent(  )
{

	startTask( liftTask );

}

void driverLift(  )
{

	motor[ intake ] = vexRT[ Btn6UXmtr2 ] * 127 - vexRT[ Btn6DXmtr2 ] * 127 + 15;
	motor[ mogo ] = vexRT[ Btn5UXmtr2 ] * 127 - vexRT[ Btn5DXmtr2 ] * 127;

	if( !pressed2.b8D && vexRT[ Btn8DXmtr2 ] )
  	stackCurrent();
  if( deadzone( vexRT[ Ch3Xmtr2 ] ) != 0 )
  {

  	stopTask( liftTask );
  	setLift( vexRT[ Ch3Xmtr2 ] );

  }
  if( deadzone( vexRT[ Ch2Xmtr2 ] ) != 0 )
  {

  	stopTask( liftTask );
  	setChainbar( vexRT[ Ch2Xmtr2 ] );

  }

}
