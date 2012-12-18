// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include "makewalk.hpp"



//歩行の更新
void MakeWalk::update(double joint[], double velocity[], double walkx, double walky,double rotation, bool act =1)
{
	//足の高さを定義
	legheight = -zc+0.05-0.083;
	double rankle[3],lankle[3];
	//足上げと足下げに使用する時間の差
	STATEDIFF = -0.02;//Tsupが0.04の倍数ではない場合、-0.03にする
	//現在の関節角度の更新
	JointUpdate(joint);
	
	//周期更新
	if(t > nextstatetime){
		state++;
		//両脚支持をしない場合
		if(!doublesupportflag){
			if(state == 2 || state == 5){
				state++;
			}
		}
		//上限なので戻る
		if(state > 5){
			state = 0;
		}
		//以前の目標の足首の位置を記憶する
		for(int i=0;i<3;i++){
			brpos[i] = rpos[i];
			blpos[i] = lpos[i];
		}
		for(int i = 0;i<7;i++){
			brangle[i] = rangle[i];
			blangle[i] = langle[i];
		}
		r_toeangle = 0;
		l_toeangle = 0;
		if(state == 3 || state == 0){
			double bstridex = sx;//一つ前の歩幅
			double bstridey = sidesy;
			double bstrider = sr;
			sx = walkx;
			sidesy = walky;
			sr= rotation;
			//反対方向へ移動する時は、0を挟む
			if((sx > 0 && bstridex < 0) || (sx < 0 && bstridex > 0)){
				onx = -1;
			}
			if((sidesy > 0 && bstridey < 0) || (sidesy < 0 && bstridey > 0)){
				ony = 0;
			}
			if((sr > 0 && bstrider < 0) || (sr < 0 && bstrider > 0)){
				onr = -1;
			}
			if(onx < 1){
				sx = 0;
				onx++;
			}
			if(ony < 1){
				sidesy = 0;
				ony++;
			}
			if(onr < 1){
				sr = 0;
				onr++;
			}
		}
		//回転処理
		if(state == 0 || state == 3){
			double maxrotation = 90;
			if(sr > maxrotation*DEGTORAD){
				sr = maxrotation*DEGTORAD;
			}else if(sr < -maxrotation*DEGTORAD){
				sr = -maxrotation*DEGTORAD;
			}
			(this)->nexttheta += sr;
		}
		switch(state){
			case -2://重心を落とす
				bl_toeangle = br_toeangle = l_toeangle = r_toeangle = 0;
				break;
			case -1://初歩目の両脚支持
				//次の時間を更新
				nextsuptime += dblhalf;
				nextstatetime += dblhalf;
				break;
			case 0://足の上げ始め
			case 3:
				bx = rx;
				by = ry;
				RoboCalcPendulum(&rx,&ry, &rzx, &rzy);
				nextstatetime += Tsup/2-STATEDIFF;
				nextsuptime += Tsup;
				break;
			case 2://両脚支持の開始
			case 5:
				nextsuptime += dbl;
				nextstatetime += dbl;
				break;
			default://足下げ時
				nextstatetime += Tsup/2+STATEDIFF;
				break;
		}
	}
	//ゴミをなくすための丸め込み
	nextstatetime = round(nextstatetime*100)*0.01;
	nextsuptime = round(nextsuptime*100)*0.01;
	
	//重心位置の計算
	switch(state){
		case -1:
			//両脚支持期間の計算
			DoubleSupport(dblhalf-(nextstatetime-t));
			break;
		case 0:
		case 1:
		case 3:
		case 4:
			//片足支持期間の計算
			COMCalculation(Tsup-(nextsuptime-t));
			break;
		case 2:
		case 5:
			//両脚支持期間の計算
			DoubleSupport(dbl-(nextstatetime-t));
			break;
		default:
			break;
	}
	//前方向への移動の場合の
	//接地角度
	landingpoints = rx- ((x_f_2-new_p_x_1)*cosh(Tsup/TC)+TC*dx_f_2*sinh(Tsup/TC)+new_p_x_1);
	if(landingpoints > 0){
		toeangle = fabs(landingpoints*2)*42*DEGTORAD;
		if(toeangle > 10*DEGTORAD){
				toeangle = 10*DEGTORAD;
			}
			heelangle = fabs(landingpoints*2)*50*DEGTORAD;
			if(heelangle > 10*DEGTORAD){
				heelangle = 10*DEGTORAD;
			}
		}else if(landingpoints < 0){//後ろへの移動の場合。接地と離陸が逆になる
			toeangle = fabs(landingpoints*2)*25*DEGTORAD;
			if(toeangle > 10*DEGTORAD){
				toeangle = 10*DEGTORAD;
			}
			heelangle = fabs(landingpoints*2)*25*DEGTORAD;
			if(heelangle > 10*DEGTORAD){
				heelangle = 10*DEGTORAD;
			}
			heelangle = 0;
			toeangle = 0;
		}
	//腕振り生成
	//MakeArmSwing(velocity);
	//足首位置決定
	setAnklePos();
	if(state == -2){
		LegTrajectory(t,nextstatetime,rpos,brpos,rpos);
		LegTrajectory(t,nextstatetime,lpos,blpos,lpos);
	}
	//方向転換のヨー軸の回転の決定
	setYawAngle();
	double tmppos[3] = {0,0,0};
	double tp[3], p1[3];
	for(int i = 0; i < 3; i++){
		tmppos[i] = rpos[i];
	}
	tp[0] = -tmppos[1];
	tp[1] = tmppos[0];
	tp[2] = tmppos[2];
		
	//逆運動学により、目標角度を計算
	//右脚
	RightLegIK(rangle, tp,right_yaw);
	for(int i = 0; i < 3; i++){
		tmppos[i] = lpos[i];
	}
	tp[0] = -tmppos[1];
	tp[1] = tmppos[0];
	tp[2] = tmppos[2];
	//左脚
	LeftLegIK(langle, tp,left_yaw);
	
	//つま先・かかとの角度をセット
	setHeelToe(rangle,langle);
	//関節角度空間での軌道生成
	if(state == 0){
		AngleTrajectory(Tsup/2-STATEDIFF-(nextstatetime-t),Tsup/2-STATEDIFF, blangle, langle);
	}else if(state == 1){
		AngleTrajectory(Tsup/2+STATEDIFF-(nextstatetime-t),Tsup/2+STATEDIFF, blangle, langle);
	}else if(state == 3){
		AngleTrajectory(Tsup/2-STATEDIFF-(nextstatetime-t),Tsup/2-STATEDIFF, brangle, rangle);
	}else if(state == 4){
		AngleTrajectory(Tsup/2+STATEDIFF-(nextstatetime-t),Tsup/2+STATEDIFF, brangle, rangle);
	}
/**/
	//逆運動学により求められた角度から
	//指令値を作成
	const bool VelocityCheck = true;
	LegVelocity(rangle, rvelocity, VelocityCheck);
	LegVelocity(langle, lvelocity, VelocityCheck);
	//指令値の出力
	OutputCommand(velocity);

	//時間経過
	timeupdate();
}


//歩行の更新
//angle version
void MakeWalk::update(double joint[], double walkx, double walky,double rotation, bool act =1)
{
	//足の高さを定義
	legheight = -zc+0.05-0.083;
	double rankle[3],lankle[3];
	//足上げと足下げに使用する時間の差
	STATEDIFF = -0.02;//Tsupが0.04の倍数ではない場合、-0.03にする
	//現在の関節角度の更新
	JointUpdate(joint);
	
	//周期更新
	if(t > nextstatetime){
		state++;
		//両脚支持をしない場合
		if(!doublesupportflag){
			if(state == 2 || state == 5){
				state++;
			}
		}
		//上限なので戻る
		if(state > 5){
			state = 0;
		}
		//以前の目標の足首の位置を記憶する
		for(int i=0;i<3;i++){
			brpos[i] = rpos[i];
			blpos[i] = lpos[i];
		}
		for(int i = 0;i<7;i++){
			brangle[i] = rangle[i];
			blangle[i] = langle[i];
		}
		r_toeangle = 0;
		l_toeangle = 0;
		if(state == 3 || state == 0){
			double bstridex = sx;//一つ前の歩幅
			double bstridey = sidesy;
			double bstrider = sr;
			sx = walkx;
			sidesy = walky;
			sr= rotation;
			//反対方向へ移動する時は、0を挟む
			if((sx > 0 && bstridex < 0) || (sx < 0 && bstridex > 0)){
				onx = -1;
			}
			if((sidesy > 0 && bstridey < 0) || (sidesy < 0 && bstridey > 0)){
				ony = 0;
			}
			if((sr > 0 && bstrider < 0) || (sr < 0 && bstrider > 0)){
				onr = -1;
			}
			if(onx < 1){
				sx = 0;
				onx++;
			}
			if(ony < 1){
				sidesy = 0;
				ony++;
			}
			if(onr < 1){
				sr = 0;
				onr++;
			}
		}
		//回転処理
		if(state == 0 || state == 3){
			double maxrotation = 90;
			if(sr > maxrotation*DEGTORAD){
				sr = maxrotation*DEGTORAD;
			}else if(sr < -maxrotation*DEGTORAD){
				sr = -maxrotation*DEGTORAD;
			}
			(this)->nexttheta += sr;
		}
		switch(state){
			case -2://重心を落とす
				bl_toeangle = br_toeangle = l_toeangle = r_toeangle = 0;
				break;
			case -1://初歩目の両脚支持
				//次の時間を更新
				nextsuptime += dblhalf;
				nextstatetime += dblhalf;
				break;
			case 0://足の上げ始め
			case 3:
				bx = rx;
				by = ry;
				RoboCalcPendulum(&rx,&ry, &rzx, &rzy);
				nextstatetime += Tsup/2-STATEDIFF;
				nextsuptime += Tsup;
				break;
			case 2://両脚支持の開始
			case 5:
				nextsuptime += dbl;
				nextstatetime += dbl;
				break;
			default://足下げ時
				nextstatetime += Tsup/2+STATEDIFF;
				break;
		}
	}
	//ゴミをなくすための丸め込み
	nextstatetime = round(nextstatetime*100)*0.01;
	nextsuptime = round(nextsuptime*100)*0.01;
	
	//重心位置の計算
	switch(state){
		case -1:
			//両脚支持期間の計算
			DoubleSupport(dblhalf-(nextstatetime-t));
			break;
		case 0:
		case 1:
		case 3:
		case 4:
			//片足支持期間の計算
			COMCalculation(Tsup-(nextsuptime-t));
			break;
		case 2:
		case 5:
			//両脚支持期間の計算
			DoubleSupport(dbl-(nextstatetime-t));
			break;
		default:
			break;
	}
	//前方向への移動の場合の
	//接地角度
	landingpoints = rx- ((x_f_2-new_p_x_1)*cosh(Tsup/TC)+TC*dx_f_2*sinh(Tsup/TC)+new_p_x_1);
	if(landingpoints > 0){
		toeangle = fabs(landingpoints*2)*42*DEGTORAD;
		if(toeangle > 10*DEGTORAD){
				toeangle = 10*DEGTORAD;
			}
			heelangle = fabs(landingpoints*2)*50*DEGTORAD;
			if(heelangle > 10*DEGTORAD){
				heelangle = 10*DEGTORAD;
			}
		}else if(landingpoints < 0){//後ろへの移動の場合。接地と離陸が逆になる
			toeangle = fabs(landingpoints*2)*25*DEGTORAD;
			if(toeangle > 10*DEGTORAD){
				toeangle = 10*DEGTORAD;
			}
			heelangle = fabs(landingpoints*2)*25*DEGTORAD;
			if(heelangle > 10*DEGTORAD){
				heelangle = 10*DEGTORAD;
			}
			heelangle = 0;
			toeangle = 0;
		}
	//腕振り生成
	//MakeArmSwing(velocity);
	//足首位置決定
	setAnklePos();
	if(state == -2){
		LegTrajectory(t,nextstatetime,rpos,brpos,rpos);
		LegTrajectory(t,nextstatetime,lpos,blpos,lpos);
	}
	//方向転換のヨー軸の回転の決定
	setYawAngle();
	double tmppos[3] = {0,0,0};
	double tp[3], p1[3];
	for(int i = 0; i < 3; i++){
		tmppos[i] = rpos[i];
	}
	tp[0] = -tmppos[1];
	tp[1] = tmppos[0];
	tp[2] = tmppos[2];
		
	//逆運動学により、目標角度を計算
	//右脚
	RightLegIK(rangle, tp,right_yaw);
	for(int i = 0; i < 3; i++){
		tmppos[i] = lpos[i];
	}
	tp[0] = -tmppos[1];
	tp[1] = tmppos[0];
	tp[2] = tmppos[2];
	//左脚
	LeftLegIK(langle, tp,left_yaw);
	
	//つま先・かかとの角度をセット
	setHeelToe(rangle,langle);
	//関節角度空間での軌道生成
	if(state == 0){
		AngleTrajectory(Tsup/2-STATEDIFF-(nextstatetime-t),Tsup/2-STATEDIFF, blangle, langle);
	}else if(state == 1){
		AngleTrajectory(Tsup/2+STATEDIFF-(nextstatetime-t),Tsup/2+STATEDIFF, blangle, langle);
	}else if(state == 3){
		AngleTrajectory(Tsup/2-STATEDIFF-(nextstatetime-t),Tsup/2-STATEDIFF, brangle, rangle);
	}else if(state == 4){
		AngleTrajectory(Tsup/2+STATEDIFF-(nextstatetime-t),Tsup/2+STATEDIFF, brangle, rangle);
	}
/*
	//逆運動学により求められた角度から
	//指令値を作成
	const bool VelocityCheck = true;
	LegVelocity(rangle, rvelocity, VelocityCheck);
	LegVelocity(langle, lvelocity, VelocityCheck);
	//指令値の出力
	OutputCommand(velocity);
*/

	for (int i = 0; i < 6; i++)
	{
		joint[i] = langle[i];
	}
	for (int i = 0; i < 6; i++)
	{
		joint[i+6] = rangle[i];
	}

	//時間経過
	timeupdate();
}
