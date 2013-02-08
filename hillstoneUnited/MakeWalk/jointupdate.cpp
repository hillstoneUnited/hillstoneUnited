// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"

void MakeWalk::JointUpdate(double joint[]){
	//左脚
	n_langle[0] = -1;
	n_langle[1] = joint[0]*RADTODEG;
	n_langle[2] = joint[1]*RADTODEG;
	n_langle[3] = joint[2]*RADTODEG;
	n_langle[4] = joint[3]*RADTODEG;
	n_langle[5] = joint[4]*RADTODEG;
	n_langle[6] = joint[5]*RADTODEG;
	//右脚
	n_rangle[0] = 1;
	n_rangle[1] = joint[6]*RADTODEG;
	n_rangle[2] = joint[7]*RADTODEG;
	n_rangle[3] = joint[8]*RADTODEG;
	n_rangle[4] = joint[9]*RADTODEG;
	n_rangle[5] = joint[10]*RADTODEG;
	n_rangle[6] = joint[11]*RADTODEG;
	
	//足の傾きの更新
	br_toeangle = r_toeangle;//-(n_rangle[3] + n_rangle[4] + n_rangle[5])*M_PI/180;
	bl_toeangle = l_toeangle;//-(n_langle[3] + n_langle[4] + n_langle[5])*M_PI/180;
}




