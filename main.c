#pragma config(Sensor, in1,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    mogoPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    lLine,          sensorLineFollower)
#pragma config(Sensor, in4,    rLine,          sensorLineFollower)
#pragma config(Sensor, in7,    pwrExpStatus,   sensorAnalog)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  lEnc,           sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rEnc,           sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  chainbarEnc,    sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  mogoTouch,      sensorTouch)
#pragma config(Motor,  port1,           mogo,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           fR,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           bL,            tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           lLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rLift,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           rChain,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           lChain,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           bR,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           fL,            tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          intake,        tmotorVex393HighSpeed_HBridge, openLoop)
#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"
#include "general.h"
#include "motion.h"
#include "lift.h"
#include "manipulators.h"
#include "chassis.h"
#include "auton.h"
#include "lcd.h"

void pre_auton()
{

	bStopTasksBetweenModes = false;
	bDisplayCompetitionStatusOnLcd = false;

	PIDInit( distancePIDValues, 0, 0, 0, 0, 0, lEnc, 10, 10 );
	PIDInit( turnPIDValues, 0, 0, 0, 0, 0, gyro, 10, 10 );
	PIDInit( mogoPIDValues, 0, 0, 0, 0, 0, mogoPot, 10, 10 );
	PIDInit( liftPIDValues, 0, 0, 0, 0, 0, liftPot, 10, 10 );

}

task autonomous()
{



}

task usercontrol()
{

	startTask( PIDLoop );

  while (true)
  {

  	wait1Msec( 20 );

  }

}
