//	Return a value capped at a specified integer
int capVal( int value, int maxValue = 127 )
{

	if( abs( value ) > maxValue )
		value = maxValue * sgn( value );

	return value;

}

//	Return a value if it's above or below a threshold
int deadzone( int value, int deadspace = 20 )
{

	if( abs(value) < deadspace )
		return 0;
	else
		return value;

}

//	Returns a value that is capped between a range
int capMinMax( int value, int minValue = 0, int maxValue )
{

	if( value < minValue )
		value = minValue;
	else if( value > maxValue )
		value = maxValue;

	return value;

}

float map( float value, float start1, float stop1, float start2, float stop2 )
{

	return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));

}

/* Button-Related Code */

/*	Struct containing booleans for all buttons on Vex Joystick. */
typedef struct
{
	/* RobotC Btn #'s: */
	bool b5D; // 14
	bool b5U; // 15
	bool b6D; // 16
	bool b6U; // 17
	bool b8D; // 18
	bool b8L; // 19
	bool b8U; // 20
	bool b8R; // 21
	bool b7D; // 22
	bool b7L; // 23
	bool b7U; // 24
	bool b7R; // 25

} btnData;

/* Init structs for keeping track of previously pressed and toggled buttons */
btnData pressed;
btnData toggled;
btnData pressed2;
btnData toggled2;

/*	Button toggled check - used to check whether a button has been toggled
 *		-	checks if a button is already pressed - will not rapid-toggle
 *	Usage:
 *		-	input Btn##, pressed.b##, and toggled.b##
 *		-	loop function for constant update
 *	Example:
 *		-	btnToggle( Btn5D, pressed.b5D, toggled.b5D );
 */
bool btnToggle( TVexJoysticks btnCurrent, bool &btnPressed, bool &btnToggled )
{

	if( vexRT[btnCurrent] && !btnPressed )
	{

		btnToggled = !btnToggled;

		btnPressed = true;

	}
	else if( !vexRT[btnCurrent] && btnPressed )
		btnPressed = false;

	return btnToggled;

}

/*	All button toggled check - used to update whether any button has been toggled
 *		-	checks if any button is already pressed - will not rapid-toggle
 *	Usage:
 *		-	loop function for constant update of all buttons in btnToggled struct
 *	Example:
 *		-	updateAllBtnToggle();
 */
void updateAllBtnToggle()
{
	bool *toggledI;
	bool *pressedI;
	bool *toggled2I;
	bool *pressed2I;
	toggledI = &toggled.b5D;
	pressedI = &pressed.b5D;
	toggled2I = &toggled2.b5D;
	pressed2I = &pressed2.b5D;

	for( int i = 0; i < sizeof( toggled ); i++ )
	{

		if( vexRT[Btn5D + i] && !*pressedI )
		{

			*toggledI = !*toggledI;

			*pressedI = true;

		}
		else if( !vexRT[Btn5D + i] && *pressedI )
			*pressedI = false;

		toggledI++;
		pressedI++;

	}
	for( int i = 0; i < sizeof( toggled2 ); i++ )
	{

		if( vexRT[Btn5DXmtr2 + i] && !*pressed2I )
		{

			*toggled2I = !*toggled2I;

			*pressed2I = true;

		}
		else if( !vexRT[Btn5DXmtr2 + i] && *pressed2I )
			*pressed2I = false;

		toggled2I++;
		pressed2I++;

	}

}
