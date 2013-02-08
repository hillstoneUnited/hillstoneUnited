// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"

MakeWalk::MakeWalk(): 
	SIMGAIN(0.00030558), 
	UPPERLEG(sqrt(0.120*0.120+0.005*0.005)),
	LOWERLEG(0.1),
	ANCLEFOOT(sqrt(0.035*0.035+0.030*0.030)), 
	FOOTX(0.08), 
	MAXSPEED(351),
	DEGTORAD(M_PI/180.0),
	RADTODEG(180.0/M_PI),
	OFFSET(acos(0.12/(sqrt(0.120*0.120+0.005*0.005)))*(180/M_PI)),
	ANKLE_OFFSET(-0.035),
	TOELENGTH(0.11),
	HEELLENGTH(0.05),
	FOOTSIDELENGTH(0.04),
	ANKLETOFOOT(0.05)
	{	init();	}
