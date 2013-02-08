// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"

//-----------------------------------------------------------------------
//踵接地時の足首角度の変化
//@in time = (nextsuptime - nowtime)
//
//-----------------------------------------------------------------------
void MakeWalk::HeelAngle(double time, double pos[]){
	time *= 1000;
	time = round(time);
	time /= 1000;
	if(!doublesupportflag){
		time = Tsup/2 - time;
		time *= 1000;
		time = round(time);
		time /= 1000;
		if(heeltime >= time){
			double a = 1 - (time / heeltime);
			if(landingpoints >= 0){
				pos[0] = pos[0] - (HEELLENGTH)*(1-cos(heelangle*a));// + (ANKLETOFOOT * cos(M_PI/2+heelangle))
				pos[2] = pos[2] + HEELLENGTH*sin(heelangle*a);// - (ANKLETOFOOT - ANKLETOFOOT * sin(M_PI/2+heelangle));
			}else if(landingpoints < 0){
				pos[0] = pos[0] + (TOELENGTH)*(1-cos(toeangle*a));
				pos[2] = pos[2] +  TOELENGTH*sin(toeangle*a);
			}
		}
	}else if(doublesupportflag){
		time = dbl - time;
		time *= 1000;
		time = round(time);
		time /= 1000;
		//printf("time = %lf\n", time);
		if(dblheeltime >= time){
			double a = 1 - (time / dblheeltime);
			//printf("a = %lf\n", a);
			if(landingpoints >= 0){
				pos[0] = pos[0] - (HEELLENGTH)*(1-cos(heelangle*a));// + (ANKLETOFOOT * cos(M_PI/2+heelangle))
				pos[2] = pos[2] + HEELLENGTH*sin(heelangle*a);// - (ANKLETOFOOT - ANKLETOFOOT * sin(M_PI/2+heelangle));
			}else if(landingpoints < 0){
				pos[0] = pos[0] + (TOELENGTH)*(1-cos(toeangle*a));
				pos[2] = pos[2] +  TOELENGTH*sin(toeangle*a);
			}
		}
	}
}

//-----------------------------------------------------------------------
//爪先離陸時の足首角度の変化
//@in time = (nextstatetime - nowtime)
//
//-----------------------------------------------------------------------
void MakeWalk::ToeAngle(double time, double pos[]){
	time *= 1000;
	time = round(time);
	time /= 1000;
	if(toetime >= time && !doublesupportflag){
		double a =1 - (time/ toetime);
		if(landingpoints >= 0){
			pos[0] = pos[0] + TOELENGTH*(1-cos(toeangle*a));// + (ANKLETOFOOT*sin(toeangle*a));
			pos[2] = pos[2] + TOELENGTH*sin(toeangle*a);// - (ANKLETOFOOT * (1-cos(toeangle*a)));
		}else if(landingpoints < 0){
			pos[0] = pos[0] - HEELLENGTH*(1-cos(heelangle*a));
			pos[2] = pos[2] + TOELENGTH*sin(heelangle*a);
		}
	}
	if(dbltoetime >= time && doublesupportflag){
		double a =1 - (time/ dbltoetime);
				//printf("time = %lf\n", time);
		if(landingpoints >= 0){
			pos[0] = pos[0] + TOELENGTH*(1-cos(toeangle*a));// + (ANKLETOFOOT*sin(toeangle*a));
			pos[2] = pos[2] + TOELENGTH*sin(toeangle*a);// - (ANKLETOFOOT * (1-cos(toeangle*a)));
		}else if(landingpoints < 0){
			pos[0] = pos[0] - HEELLENGTH*(1-cos(heelangle*a));
			pos[2] = pos[2] + TOELENGTH*sin(heelangle*a);
		}
	}
}


void MakeWalk::setHeelToe(double rangle[], double langle[]){
	double time;
	//ピッチ補正の追加
	switch(state){
		case 3:
			rangle[5] += -heelangle*RADTODEG*0.6;
			langle[5] += 0;
			time = Tsup/2 - (nextstatetime - t);
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(heeltime >= time && !doublesupportflag){
				double a = 1 - (time / heeltime);
				if(landingpoints >= 0){
					langle[5] += heelangle*RADTODEG * a;
				}else if(landingpoints < 0){
					langle[5] += -toeangle*RADTODEG * a;
				}
			}
			break;
		case 4:
			if(landingpoints >= 0){
				rangle[5] += heelangle*RADTODEG;
			}else if(landingpoints < 0){
				rangle[5] += -toeangle*RADTODEG;
			}
			langle[5] += 0;
			time = nextstatetime - t;
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(toetime >= time && !doublesupportflag){
				double a = 1 - (time/toetime);
				if(landingpoints >= 0){
					langle[5] += -toeangle*RADTODEG*a;
					l_toeangle = -toeangle;
				}else if(landingpoints < 0){
					langle[5] += heelangle*RADTODEG*a;
					l_toeangle = heelangle;
				}
			}
			break;
		case 5:
			time = Tsup/2 - (nextstatetime - t);
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(dblheeltime >= time && doublesupportflag){
				double a = 1 - (time / dblheeltime);
				if(landingpoints >= 0){
					rangle[5] += heelangle*RADTODEG * a;
				}else if(landingpoints < 0){
					rangle[5] += -toeangle*RADTODEG * a;
				}
			}
			time = nextstatetime - t;
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(dbltoetime >= time && doublesupportflag){
				double a = 1 - (time/dbltoetime);
				if(landingpoints >= 0){
					langle[5] += -toeangle*RADTODEG*a;
					l_toeangle = -toeangle;
				}else if(landingpoints < 0){
					langle[5] += heelangle*RADTODEG*a;
					l_toeangle = heelangle;
				}
			}
			break;
		case 0:
			rangle[5] += 0;
			langle[5] += -heelangle*RADTODEG*0.6;
			time = Tsup/2 - (nextstatetime - t);
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(heeltime >= time && !doublesupportflag){
				double a = 1 - (time / heeltime);
				if(landingpoints >= 0){
					rangle[5] += heelangle*RADTODEG * a;
				}else if(landingpoints < 0){
					rangle[5] += -toeangle*RADTODEG * a;
				}
			}
			break;
		case 1:
			rangle[5] += 0;
			if(landingpoints >= 0){
				langle[5] += heelangle*RADTODEG;
			}else if(landingpoints < 0){
				langle[5] += -toeangle*RADTODEG;
			}
			time = nextstatetime - t;
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(toetime >= time && !doublesupportflag){
				double a = 1 - (time/toetime);
				if(landingpoints >= 0){
					rangle[5] += -toeangle*RADTODEG*a;
					r_toeangle = -toeangle;
				}else if(landingpoints < 0){
					rangle[5] += heelangle*RADTODEG*a;
					r_toeangle = heelangle;
				}
			}
			break;
		case 2:
			time = Tsup/2 - (nextstatetime - t);
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(heeltime >= time && !doublesupportflag){
				double a = 1 - (time / heeltime);
				if(landingpoints >= 0){
					langle[5] += heelangle*RADTODEG * a;
				}else if(landingpoints < 0){
					langle[5] += -toeangle*RADTODEG * a;
				}
			}
			time = nextstatetime - t;
			time *= 1000;
			time = round(time);
			time /= 1000;
			if(dbltoetime >= time && doublesupportflag){
				double a = 1 - (time/dbltoetime);
				if(landingpoints >= 0){
					rangle[5] += -toeangle*RADTODEG*a;
					r_toeangle = -toeangle;
				}else if(landingpoints < 0){
					rangle[5] += heelangle*RADTODEG*a;
					r_toeangle = heelangle;
				}
			}
			break;
	}
}
