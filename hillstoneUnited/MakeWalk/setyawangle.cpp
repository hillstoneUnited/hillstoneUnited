// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"


void MakeWalk::setYawAngle(){
	if(theta -beforetheta > 0){
		if(state == 0 || state == 1){//右足支持脚時
			left_yaw = (theta-beforetheta)*(Tsup-(nextsuptime-t))/Tsup;
			right_yaw = 0;
		}else if(state == 2){//両脚支持期間
			left_yaw = (theta-beforetheta);
			right_yaw = 0;
		}else if(state == 3 || state == 4){
			left_yaw = (theta-beforetheta)*(nextsuptime-t)/Tsup;
			right_yaw = 0;
		}else if(state == 5){//脚降ろし及び両脚支持時
			left_yaw = 0;
			right_yaw = 0;
		}
	}else if(theta -beforetheta < 0){
		if(state == 3 || state == 4){//支持脚時
			right_yaw = (theta-beforetheta)*(Tsup-(nextsuptime-t))/Tsup;
			left_yaw = 0;
		}else if(state == 5){//両脚支持期間
			right_yaw = (theta-beforetheta);
			left_yaw = 0;
		}else if(state == 0 || state == 1){
			right_yaw = (theta-beforetheta)*(nextsuptime-t)/Tsup;
			left_yaw = 0;
		}else if(state == 2){//脚降ろし及び両脚支持時
			right_yaw = 0;
			left_yaw = 0;
		}
	}else{
		right_yaw = 0;
		left_yaw = 0;
	}
}
