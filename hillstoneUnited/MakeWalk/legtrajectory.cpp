// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"./makewalk.hpp"

/*---------------------------------------------------------------------------------------------------------------*/
//目標座標位置への中間の位置を線形補間を用いて作成する
//double time 時間
//double dpos[] 目標座標位置
//double npos[] timeが0の時の座標位置
//double rpos[] 線形補間した結果の座標位置
/*---------------------------------------------------------------------------------------------------------------*/
void MakeWalk::LegTrajectory(double time,double time2, double dpos[], double npos[], double rpos[])
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
	for(int i=0; i < 3; i++){
		rpos[i] = npos[i] + a*(dpos[i]-npos[i]);
	}
}
