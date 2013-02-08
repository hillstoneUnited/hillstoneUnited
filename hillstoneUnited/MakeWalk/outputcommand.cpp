// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"

void MakeWalk::OutputCommand(double velocity[]){
	velocity[0] = lvelocity[1];
	velocity[1] = lvelocity[2];
	velocity[2] = lvelocity[3]*-1;
	velocity[3] = lvelocity[4]*-1;
	velocity[4] = lvelocity[5]*-1;
	velocity[5] = lvelocity[6];
	velocity[6] = rvelocity[1];
	velocity[7] = rvelocity[2];
	velocity[8] = rvelocity[3]*-1;
	velocity[9] = rvelocity[4]*-1;
	velocity[10] = rvelocity[5]*-1;
	velocity[11] = rvelocity[6];
}
