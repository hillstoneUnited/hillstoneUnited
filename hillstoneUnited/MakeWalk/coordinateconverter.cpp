// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"


//-------------------------------------------------
//座標変換用関数
//-------------------------------------------------
void MakeWalk::coordinateConverter(double v[]){
	double tmp;
	tmp = v[0];
	v[0] = v[1];
	v[1] = -tmp;
}
