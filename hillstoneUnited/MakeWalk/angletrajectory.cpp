// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"


void MakeWalk::AngleTrajectory(double time, double time2, double nset[], double dset[])
{
	double a = time / time2;
	a *= 1000;
	a = round(a);
	a *= 0.001;
	if( a > 1){
		a = 1;
	}else if(a < 0){
		a = 0;
	}
	for(int i = 1;i<7;i++){
		dset[i] = nset[i] + a*(dset[i]-nset[i]);
	}
}
