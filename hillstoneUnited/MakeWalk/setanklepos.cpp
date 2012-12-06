// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"

void MakeWalk::setAnklePos(){
	//右足制御
	switch (state){
		case 3://脚上げ
			if(landingpoints >= 0){
				rpos[0] = ANKLE_OFFSET - landingpoints * 0.05;
			}else if(landingpoints <0){
				rpos[0] = ANKLE_OFFSET + landingpoints * 0.25;
			}
			rpos[1] = ry- ((y_f_2-new_p_y_1)*cosh(Tsup/TC/2)+TC*dy_f_2*sinh(Tsup/TC/2)+new_p_y_1);
			rpos[2] = legheight+upleg;
			break;
		case 4://脚下げ
			if(sx >= 0){//前進の場合
				rpos[0] = landingpoints + ANKLE_OFFSET - (HEELLENGTH)*(1-cos(heelangle));// + (ANKLETOFOOT * cos(M_PI/2+heelangle));
				rpos[2] = legheight + HEELLENGTH*sin(heelangle) - (ANKLETOFOOT - ANKLETOFOOT * sin(M_PI/2+heelangle));
			}else if(sx < 0){//後進の場合
				rpos[0] = landingpoints + ANKLE_OFFSET + (TOELENGTH)*(1-cos(toeangle));
				rpos[2] = legheight + TOELENGTH*sin(toeangle);
			}
			rpos[1] = ry- ((y_f_2-new_p_y_1)*cosh(Tsup/TC)+TC*dy_f_2*sinh(Tsup/TC)+new_p_y_1);
			break;
		case 0: //支持脚
			rpos[0] = (bx-x_f2 + ANKLE_OFFSET);
			rpos[1] = by-y_f2;
			rpos[2] = legheight;
			if(!doublesupportflag){
				HeelAngle(nextstatetime - t, rpos);
			}
			break;
		case 1:
			rpos[0] = (bx-x_f2 + ANKLE_OFFSET);
			rpos[1] = by-y_f2;
			rpos[2] = legheight;
			//離陸時
			if(!doublesupportflag){
				ToeAngle(nextstatetime - t, rpos);
			}
			break;
		case 5:
			rpos[0] = (rx-x_f2 + ANKLE_OFFSET);
			rpos[1] = ry-y_f2;
			rpos[2] = legheight;
			HeelAngle(nextstatetime - t, rpos);
			break;
		case 2:
			rpos[0] = bx-x_f2 + ANKLE_OFFSET;
			rpos[1] = by-y_f2;
			rpos[2] = legheight;
			ToeAngle(nextstatetime - t, rpos);
			break;
		case -1:
			rpos[0] = ANKLE_OFFSET;
			rpos[1] = -y_f2;
			rpos[2] = legheight;
			break;
		default:
			rpos[0] = ANKLE_OFFSET;
			rpos[1] = -y_f2;
			rpos[2] = legheight;
			break;
	}
		//左脚制御
	switch (state){
		case 3:
			lpos[0] = (bx-x_f2 + ANKLE_OFFSET);
			lpos[1] = by-y_f2;
			lpos[2] = legheight;
			//接地軌道
			if(!doublesupportflag){
				HeelAngle(nextstatetime-t, lpos);
			}
			break;
		case 4://支持脚
			lpos[0] = (bx-x_f2 + ANKLE_OFFSET);
			lpos[1] = by-y_f2;
			lpos[2] = legheight;
			if(!doublesupportflag){
				ToeAngle(nextstatetime-t, lpos);
			}
			break;
		case 0: //脚上げ
			if(sx >= 0){
				lpos[0] = ANKLE_OFFSET - sx * 0.05;
			}else if(sx <0){
				lpos[0] = ANKLE_OFFSET + sx * 0.25;
			}
			lpos[1] = ry- ((y_f_2-new_p_y_1)*cosh(Tsup/TC/2)+TC*dy_f_2*sinh(Tsup/TC/2)+new_p_y_1);;
			lpos[2] = legheight+upleg;
			break;
		case 1://脚下ろし
			if(sx >= 0){//前進の場合
				lpos[0] = landingpoints + ANKLE_OFFSET - HEELLENGTH*(1-cos(heelangle));// + (ANKLETOFOOT * cos(M_PI/2+heelangle));
				lpos[2] = legheight + HEELLENGTH*sin(heelangle) - (ANKLETOFOOT - ANKLETOFOOT * sin(M_PI/2+heelangle));
			}else if(sx < 0){//後進の場合
				lpos[0] = landingpoints + ANKLE_OFFSET + TOELENGTH*(1-cos(toeangle));
				lpos[2] = legheight + TOELENGTH*sin(toeangle);
			}
			lpos[1] = ry- ((y_f_2-new_p_y_1)*cosh(Tsup/TC)+TC*dy_f_2*sinh(Tsup/TC)+new_p_y_1);
			break;
		case 5:
			lpos[0] = (bx-x_f2 + ANKLE_OFFSET);
			lpos[1] = by-y_f2;
			lpos[2] = legheight;
			ToeAngle(nextstatetime - t, lpos);
			break;
		case 2:
			lpos[0] = (rx-x_f2 + ANKLE_OFFSET);
			lpos[1] = ry-y_f2;
			lpos[2] = legheight;
			HeelAngle(nextstatetime - t, lpos);
			break;
		case -1://最初の両脚支持
			lpos[0] = ANKLE_OFFSET;
			lpos[1] = 0.110-y_f2;
			lpos[2] = legheight;
			break;
		default://重心を落とす
			lpos[0] = ANKLE_OFFSET;
			lpos[1] = 0.110-y_f2;
			lpos[2] = legheight;
			break;
	}
}
