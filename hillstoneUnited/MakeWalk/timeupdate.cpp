// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"


void MakeWalk::timeupdate(){
	t += 0.02;
	t *= 100;
	t = round(t);
	t *= 0.01;
}
