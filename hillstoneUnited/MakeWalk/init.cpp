// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"

	//歩容生成に必要なパラメータの初期化
	//直立状態での初期化
void MakeWalk::init()
{
	std::cout << "Walking Init()" << std::endl;
	doublesupportflag = false;//両脚支持をするか
	toestrike = true;//爪先離陸を行うか
	t = 0;//歩行時間
	state = -2;//歩行ステート
	//--------------------------------
	Tsup = 0.8;//歩行周期[s]
	nextstatetime = 3;//歩行開始するまでの時間[s]
	nextsuptime = nextstatetime;
	zc = (0.385-0.083)-0.035;//0.255 - 0.05;//重心の高さ(0.302-0.03)[m]
	legheight = -zc+0.05-0.083;//胴体座標系での足首のz位置[m]
	upleg = 0.03;//脚を上げる量[m]
	//--------------------------------
	//以下計算用
	sx = 0.00;//実際の前後の歩幅
	sidesy = 0.00;//左右への移動量
	beforetheta = 0;
	theta =0;
	nexttheta = 0;
	nextsx = 0;
	nextsy = 0.110;
	left_yaw = right_yaw = 0;
	rangle[0] = 1;
	langle[0] =-1; 
	brpos[1] = rpos[1] = -0.055;
	blpos[1] = lpos[1] = 0.055;
	brpos[0] = blpos[0] = rpos[0] = lpos[0] = ANKLE_OFFSET;
	brpos[2] = blpos[2] = rpos[2] = lpos[2] = -0.335;
	//zc = -1*(legheight+0.009+0.035);
	onx = 1;//歩幅を増やしてもいい場合1になる
	ony = 1;//歩幅を増やしてもいい場合1になる
	onr = 1;//回転してもいい場合1になる
 	g = 9.81;
 	TC  = sqrt(zc/g);
	C   = cosh(Tsup/TC);
	S   = sinh(Tsup/TC);

	x_f_1	   = 0;
	dx_f_1	   = 0;
	y_f_1	   = 0.055;
	dy_f_1	   =  -(C-1)/(TC*S)*y_f_1;
	new_p_x	 = 0;
	new_p_y	 = 0;
	new_x_dt = 0;
	new_y_dt = 0;
	p_x	   	 = 0;
	p_y	   	 = 0;
	p_x_1	   = 0;
	p_y_1	   = 0;
	dbl = 0;
	dblhalf = 0.08;
	
	x_f2 = 0;
	y_f2 = 0.055;
	dx_f2 = 0;
	dy_f2 = 0;
		
	//速度初期化
	for(int i = i; i<7;i++){
		rvelocity[i] = lvelocity[i] = 0;
	}
	n = 0;
	sign = -1;
	rx=0,ry=0,rzx=0,rzy=0,bx=0,by=0.110,bbx=0,bby=0;
	startflag = false;
		
		
	dy_f_1 = 0;
	new_p_x = 0;
	new_p_x_1 = 0;
	new_p_y = 0;
	new_p_y_1 = 0;
	new_x_dt = 0;
	new_y_dt = 0;
	dx_f_2 = 0;
	dy_f_2 = 0;

	
	g_ax0 = 0;
	g_ax1 = 0;
	g_ax2 = 0;
	g_ax3 = 0;
	g_ax4 = 0;
	g_ay0 = 0;
	g_ay1 = 0;
	g_ay2 = 0;
	g_ay3 = 0;
	g_ay4 = 0;
	 
	 //踵接地・爪先離陸
	heeltime = 0.02;
	toetime = 0.02;
	dblheeltime = 0.02;
	dbltoetime = 0.02;
	 
	//Tsupが0.04の倍数ではない場合、-0.03にする。
	if((int)(floor(Tsup*100))%4 == 0){
		STATEDIFF = -0.02;
	}else{
		STATEDIFF = -0.03;
	}
	double landingpoints = 0;
	double toeangle = 0;
	double heelangle = 0;
	double r_toeangle = 0;
	double l_toeangle = 0;
 	double br_toeangle = 0;
	double bl_toeangle = 0;
}

