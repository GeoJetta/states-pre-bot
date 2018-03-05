#define CHASSIS_DISTANCE_SENSOR driveEncoder

/**
 * PID controller data structure
 */
typedef struct {

	float Kp;
	float Ki;
	float Kd;
	float innerIntegralBand;
	float outerIntegralBand;
	float sigma;
	float lastValue;
	unsigned long lastTime;
	float lastSetPoint;
	int target;
	int lastTarget;
	tSensors errorSource;
	bool stopped;
	float stoppedRange;
	unsigned long startStoppedTime;
	bool complete;
	float completeRange;
	float deltaPV;
	bool stuck;
	unsigned long targetChangedTime;
	float stuckRange;

} PID;

/**
 * initialize pid structure, set parameters
 *
 * @param pid instance of PID structure
 * @param Kp  PID Kp constant
 * @param Ki  PID Ki constant
 * @param Kd  PID Kd constant
 * @param innerIntegralBand  inner bound of PID I summing cutoff
 * @param outerIntegralBand  outer bound of PID I summing cutoff
 */
void PIDInit (	PID pid, float Kp, float Ki, float Kd, float innerIntegralBand, float outerIntegralBand,
								tSensors iErrorSource, float iRange, float completeRange, float stuckRange ) {
	pid.Kp = Kp;
	pid.Ki = Ki;
	pid.Kd = Kd;
	pid.innerIntegralBand = innerIntegralBand;
	pid.outerIntegralBand = outerIntegralBand;
	pid.sigma = 0;
	pid.lastValue = 0;
	pid.lastTime = nPgmTime;
	pid.target = 0;
	pid.lastTarget = 0;
	pid.stopped = false;
	pid.errorSource = iErrorSource;
	pid.stoppedRange = iRange;
	pid.startStoppedTime = 0;
	pid.complete = false;
	pid.completeRange = completeRange;
	pid.deltaPV = 0;
	pid.stuck = false;
	pid.targetChangedTime = 0;
	pid.stuckRange = stuckRange;
}

/**
 * initialize pid structure, set parameters based on another PID structure
 *
 * @param pid  instance of PID structure
 * @param toCopy  PID instance to copy settings from
 */
void PIDInitCopy (PID pid, PID toCopy) {
	pid.Kp = toCopy.Ki;
	pid.Ki = toCopy.Ki;
	pid.Kd = toCopy.Kd;
	pid.innerIntegralBand = toCopy.innerIntegralBand;
	pid.outerIntegralBand = toCopy.outerIntegralBand;
	pid.target = toCopy.target;
	pid.lastTarget = toCopy.lastTarget;
	pid.errorSource = toCopy.errorSource;
	pid.stoppedRange = toCopy.stoppedRange;
	pid.sigma = 0;
	pid.lastValue = 0;
	pid.stopped = false;
	pid.lastTime = nPgmTime;
	pid.startStoppedTime = 0;
	pid.complete = false;
	pid.completeRange = toCopy.completeRange;
	pid.deltaPV = 0;
	pid.stuck = false;
	pid.targetChangedTime = 0;
	pid.stuckRange = toCopy.stuckRange;
}

/**
 * calculate pid output
 *
 * @param pid  instance of PID structure
 * @param setPoint  set point of PID controller
 * @param processVariable  sensor/feedback value
 *
 * @return  output value of the control loop
 */
float PIDCalc( PID pid )
{

	float PV = SensorValue[ pid.errorSource ];

	float deltaTime = ( nPgmTime - pid.lastTime ) / 1000.0;
	pid.lastTime = nPgmTime;

	float deltaPV = 0;
	if(deltaTime > 0)
		deltaPV = ( PV - pid.lastValue) / deltaTime;
	pid.lastValue = PV;
	pid.deltaPV = deltaPV;

	float error = pid.target - PV;

	if(fabs(error) > pid.innerIntegralBand && fabs(error) < pid.outerIntegralBand)
		pid.sigma += error * deltaTime;

	if (fabs (error) > pid.outerIntegralBand)
		pid.sigma = 0;

	float output = error * pid.Kp + pid.sigma * pid.Ki - deltaPV * pid.Kd;

	if( fabs( deltaPV ) < pid.stoppedRange && pid.startStoppedTime > 50.0 )
		pid.stopped = true;

	else if( fabs( deltaPV ) < pid.stoppedRange && pid.startStoppedTime == 0.0 )
		pid.startStoppedTime = nPgmTime;

	else if( fabs( deltaPV ) > pid.stoppedRange )
	{

		pid.stopped = false;
		pid.complete = false;
		pid.startStoppedTime = 0.0;

	}

	if( fabs( error ) < pid.completeRange && pid.stopped )
		pid.complete = true;

	unsigned long timeSinceTargetChange = nPgmTime - pid.targetChangedTime;

	if( pid.lastTarget != pid.target )
	{
		pid.stuck = false;
		pid.targetChangedTime = nPgmTime;
	}
	else if(	abs( error ) > pid.stuckRange
						&& pid.stopped && timeSinceTargetChange > 500 )
		pid.stuck = true;
	else if( timeSinceTargetChange > 500 && pid.stuck )
		pid.stuck = true;
	else
		pid.stuck = false;

	pid.lastTarget = pid.target;

	return output*!pid.stuck;

}

void waitForPID( PID iPID )
{

	wait1Msec( 50 );

	while( !iPID.complete || -iPID.startStoppedTime + nPgmTime > 100 )
		wait1Msec( 20 );

}
