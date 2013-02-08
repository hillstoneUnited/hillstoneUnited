// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"

/*---------------------------------------------------------------------------------------------------------------*/
//@brief 各関節のシミュレータへ送る指令値を作成する
//@param[in] double angle[] 右及び左の目標関節角度
//@param[in][out] double velocity[] 作成した指令値
//
/*---------------------------------------------------------------------------------------------------------------*/
void MakeWalk::LegVelocity(double angle[], double velocity[],bool velocityCheck = 1)
{
	const double kp = SIMGAIN * 50;
	//右脚
	if(angle[0] == 1){
		for(int i=1; i < 7; i++){
			velocity[i] = kp * (angle[i] - n_rangle[i]) - rvelocity[i];
			//速度の限界を越えているかの確認
			if(velocityCheck){
				if(SIMGAIN *  MAXSPEED < velocity[i]){
					velocity[i] = SIMGAIN * MAXSPEED;
				}else if(-SIMGAIN * MAXSPEED > velocity[i]){
					velocity[i] = -SIMGAIN * MAXSPEED;
				}
			}
		}
	}else{//左脚
		for(int i=1; i < 7; i++){
			velocity[i] = kp * (angle[i] - n_langle[i]) - lvelocity[i];
			//速度の限界を越えているかの確認
			if(velocityCheck){
				if(SIMGAIN *  MAXSPEED < velocity[i]){
					velocity[i] = SIMGAIN * MAXSPEED;
				}else if(-SIMGAIN * MAXSPEED > velocity[i]){
					velocity[i] = -SIMGAIN * MAXSPEED;
				}
			}
		}
	}
}
	/*---------------------------------------------------------------------------------------------------------------*/
	//@brief 各関節のシミュレータへ送る指令値を作成する(old)
	//@param[in] double angle[] 右及び左の目標関節角度
	//@param[in][out] double velocity[] 作成した指令値
	//
	/*---------------------------------------------------------------------------------------------------------------*/
	void MakeWalk::OldLegVelocity(double angle[], double velocity[])
	{
		const double kp = SIMGAIN * 20;
		if(angle[0] == 1){
			for(int i=1; i < 7; i++){
				velocity[i] = kp * (angle[i] - n_rangle[i]);
				//速度の限界を越えているかの確認
				if(SIMGAIN *  MAXSPEED < velocity[i]){
					velocity[i] = SIMGAIN * MAXSPEED;
				}else if(-SIMGAIN * MAXSPEED > velocity[i]){
					velocity[i] = -SIMGAIN * MAXSPEED;
				}
			}
		}else{
			for(int i=1; i < 7; i++){
				velocity[i] = kp * (angle[i] - n_langle[i]);
				//速度の限界を越えているかの確認
				if(SIMGAIN *  MAXSPEED < velocity[i]){
					velocity[i] = SIMGAIN * MAXSPEED;
				}else if(-SIMGAIN * MAXSPEED > velocity[i]){
					velocity[i] = -SIMGAIN * MAXSPEED;
				}
			}
		}
	}
