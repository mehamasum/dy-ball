//
// Project Name: Homework 5 - Bouncing Lines
//
// Name: 
//
// Date  : November 2005

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "graphics.h"

using namespace std;

#define ESC 0x1b

void welcome() 
{

	//Variable Declarations

	bool KeepGoing=true;
	bool TrailsOn=false;
	char KeyPressed;

	double ballX1, ballY1;
	double prevX1, prevY1;
	double ballX2, ballY2;
	double prevX2, prevY2;
	double ballX3, ballY3;
	double prevX3, prevY3;

	double XVel1, YVel1;
	double XVel2, YVel2;
	double XVel3, YVel3;

	int mouseX, mouseY;

	// Initial Position
	ballX1 = 150.0;
	ballY1 = 30.0;
	ballX2 = 180.0;
	ballY2 = 50.0;
	ballX3=400.0;
	ballY3=80.0;

	// Initial Velocity
	XVel1 = 5.8;
	YVel1 = 6.1;
	XVel2 = -5.8;
	YVel2 = 4.7;
	XVel3 = 3.8;
	YVel3 = 7.1;

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);

	//Main Loop
	while (!ismouseclick(WM_LBUTTONDOWN)) {
		//delay( 10 );

		// -------------------- Move and Control the Ball -------------------------

		// Remember previous position
		prevX1 = ballX1;
		prevY1 = ballY1;
		prevX2 = ballX2;
		prevY2 = ballY2;
		prevX3 = ballX3;
		prevY3 = ballY3;

		// Move the circle (Add Velocity to Position)
		ballX1 += XVel1;
		ballY1 += YVel1;
		ballX2 += XVel2;
		ballY2 += YVel2;
		ballX3 += XVel3;
		ballY3 += YVel3;

		// Erase old circles
		/*setcolor(BLACK);
		circle( (int) prevX1, (int) prevY1, 20);
		circle( (int) prevX2, (int) prevY2, 20);*/
		readimagefile("welcome2.jpg",0,0,1000,700);

		// Draw new circles
		fillellipse( (int) ballX1, (int) ballY1, 12.5,12.5);
		fillellipse( (int) ballX2, (int) ballY2, 12.5,12.5);
		fillellipse( (int) ballX3, (int) ballY3, 12.5,12.5);

		// Bounch off left/right walls
		if ( ballX1 > 980.0  || ballX1 < 30.0) {
			XVel1 *= -1.0;
		}
		if ( ballX2 > 980.0  || ballX2 < 30.0) {
			XVel2 *= -1.0;
		}
		if ( ballX3 > 980.0  || ballX3 < 30.0) {
			XVel3 *= -1.0;
		}
		// Bounch off top/bottom walls
		if ( ballY1 > 680.0  || ballY1 < 30.0) {
			YVel1 *= -1.0;
		}
		if ( ballY2 > 680.0  || ballY2 < 30.0) {
			YVel2 *= -1.0;
		}
		if ( ballY3 > 680.0  || ballY3 < 30.0) {
			YVel3 *= -1.0;
		}



		//end if mousedown()
	} // end while kbhit

} //end of main()
