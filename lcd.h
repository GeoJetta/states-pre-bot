#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

void clearLCD()
{

	clearLCDLine( 0 );
	clearLCDLine( 1 );

}

void initLCD()
{

	bLCDBacklight = true;
	clearLCD();

}

void displayCentered( const string line1, const string line2 )
{

	displayLCDCenteredString( 0, line1 );
	displayLCDCenteredString( 1, line2 );

}

void waitForRelease()
{

	while( nLCDButtons != kButtonNone )
		wait1Msec( 10 );

}

void waitForPress()
{

	while( nLCDButtons == kButtonNone )
		wait1Msec( 10 );

}

void waitForPressAndRelease()
{

	waitForPress();
	waitForRelease();

}

void battDisplay()
{

	string primaryLevel;
	sprintf( primaryLevel, "PRIMARY: %2.3f", nImmediateBatteryLevel / 1000.00 );
	displayLCDCenteredString( 0, primaryLevel );

	string expanderLevel;
	float expanderVoltage = SensorValue[ pwrExpStatus ] / 280.00;
	if( expanderVoltage < 2.0 )
	{
		playImmediateTone( 4500, 50 );
		displayLCDCenteredString( 1, "!!NO EXPANDER!!" );
		wait1Msec( 500 );
		playImmediateTone( 4500, 50 );
	}
	else
	{
		sprintf( expanderLevel, "EXPANDER: %2.3f", expanderVoltage );
		displayLCDCenteredString( 1, expanderLevel );
	}

}

int auton = 5;

string autonChoices[10] =
{	"Left Twenty",	"Right Twenty",
	"Left Five", 		"Right Five",
	"Ryan's Lefty",	"Ryan's Righty",
	"Left Defense",	"Right Defense",
	"RESTART",			"No Auton"			};

void displayAuton(){

	clearLCD();

	displayLCDChar(1, 0, 200);
	displayLCDChar(1, 6, 198);
	displayLCDChar(1, 7, 198);
	displayLCDChar(1, 15, 199);

	displayLCDCenteredString(0, autonChoices[auton]);

}

task LCD;

void runAuton()
{

	switch( auton )
	{

		case 0:
			redTwentyLeft();
		break;
		case 1:
			blueTwentyRight();
		break;
		case 2:
			redFiveLeft();
		break;
		case 3:
			blueFiveRight();
		break;
		case 4:
			redFiveLeftStat();
		break;
		case 5:
			blueFiveRightStat();
		break;
		case 6:
			leftDefense();
		break;
		case 7:
			rightDefense();
		break;
		case 8:
			startTask( LCD );
		break;
		case 9:

		break;

	}

}

task LCD
{

	battDisplay();
	waitForPressAndRelease();

	bool noButtonsPressed = true;

	displayAuton();

	while( true )
	{

		if(noButtonsPressed){ // only update auton if a button is pressed AND wasn't pressed previously
			displayAuton();
			switch(nLCDButtons){
				case kButtonLeft:
					if( auton > 0 )
						auton--;
					else
						auton = ARRAYSIZE(autonChoices);
				break;
				case kButtonCenter:
					displayLCDCenteredString( 1, "SELECT?" );
					waitForRelease();
					waitForPress();
					if( nLCDButtons == kButtonCenter )
					{
						displayLCDCenteredString( 1, "---RUNNING---" );
						stopTask(LCD);
					}
				break;
				case kButtonRight:
					clearLCD();
					if( auton < ARRAYSIZE(autonChoices) )
						auton++;
					else
						auton = 0;
				break;
			}
		}//if
		noButtonsPressed = !nLCDButtons; //update if there is a button currently pressed
		wait1Msec(20);

	}

}
