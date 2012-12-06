// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"



void MakeWalk::Gauss_J( int n, double *a, double *b )
{
  	int    p, i, j, l ; /* カウンタ   */
  double pivot, c   ; /* ピボット値 */
    
  for (p=0;p<n;p++){      /* 1行目から n行目まで繰り返す */
    pivot = a[p*n+p];        /* ピボットを取得する          */
    for (i=p;i<n;i++){  /* p行目の p列目から n列目まで */
      a[p*n+i] /= pivot;  /* 係数行列の p行を pivotで割る */
    }
    b[p] /= pivot;        /* 定数ベクトルの p行を pivotで割る */
        
    for(l=0;l<n;l++){ /* 1行目から n行目まで */        
      if (l!=p){                  /* p行を除いて  */
	c=a[l*n+p];              /* 掃き出す */
	for (j=p;j<n;j++){ 
	  a[l*n+j]-=c*a[p*n+j];
	}
	b[l]-=c*b[p];
      }
    }
  }
}

/*---------------------------------------------------------------------------------------------------------------*/
//@brief 片脚支持中の重心位置を求める
//@param[in] double time 0から周期までの時間
//
//計算結果はメンバー変数に代入される
/*---------------------------------------------------------------------------------------------------------------*/
void MakeWalk::COMCalculation(double time)
{
	x_f2  = (x_f_2-new_p_x_1)*cosh(time/TC)+TC*dx_f_2*sinh(time/TC)+new_p_x_1;
   y_f2  = (y_f_2-new_p_y_1)*cosh(time/TC)+TC*dy_f_2*sinh(time/TC)+new_p_y_1;
   dx_f2 = ((x_f_2-new_p_x_1)/TC)*sinh(time/TC)+dx_f_2*cosh(time/TC);
   dy_f2 = ((y_f_2-new_p_y_1)/TC)*sinh(time/TC)+dy_f_2*cosh(time/TC);
}


/*----------------------------------------------------------------------------------------------------------------*/
//@brief 両脚支持中の重心位置を求める
//@param[in] double dbltime 0から両脚支持期間までの時間
//
//計算結果はメンバー変数に代入される
/*----------------------------------------------------------------------------------------------------------------*/
void MakeWalk::DoubleSupport(double dbltime)
{
	if(!startflag){//最初の両脚支持時のみ
		double wdy_f,wddy_f;
		double defaulty_f = 0.055;
		double aay[3][3] = {{pow(dblhalf,2),pow(dblhalf,3),pow(dblhalf,4)},
			 {2*dblhalf,3*pow(dblhalf,2),4*pow(dblhalf,3)},
			 {2,6*dblhalf,12*pow(dblhalf,2)}};
	  double bby[3];
	  g_ax0 = 0;
	  g_ay0 = defaulty_f;//直立時の重心位置
	  g_ax1 = 0;//t:0のときの速度
	  g_ay1 = 0;
		  y_f_1  = defaulty_f*(8/10.0);
	  wdy_f  = -(C-1)/(TC*S)*y_f_1;
	  wddy_f = (g/zc)*(y_f_1);
     
  
	  bby[0]    = y_f_1-defaulty_f;
	  bby[1]    = wdy_f;
	  bby[2]    = wddy_f;
	  Gauss_J(3,(double *)aay,(double *)bby);
	
		g_ay2 = bby[0];
		g_ay3 = bby[1];
		g_ay4 = bby[2];
	
		dy_f_1  = wdy_f;//片足支持のためのパラメータ更新
	  startflag = true;
 	}
	x_f2  = g_ax0+g_ax1*dbltime+g_ax2*pow(dbltime,2)+g_ax3*pow(dbltime,3)+g_ax4*pow(dbltime,4);
 	y_f2  = g_ay0+g_ay1*dbltime+g_ay2*pow(dbltime,2)+g_ay3*pow(dbltime,3)+g_ay4*pow(dbltime,4);
  	dx_f2 = g_ax1+2*g_ax2*dbltime+3*g_ax3*pow(dbltime,2)+4*g_ax4*pow(dbltime,3);
  	dy_f2 = g_ay1+2*g_ay2*dbltime+3*g_ay3*pow(dbltime,2)+4*g_ay4*pow(dbltime,3);
}


/*----------------------------------------------------------------------------------------------------------------*/
//@brief 三次元線形倒立振子による、着地点の計算
//@param[in][out] double *x xの着地点
//@param[in][out] double *y yの着地点
/*----------------------------------------------------------------------------------------------------------------*/
void MakeWalk::RoboCalcPendulum(double *x, double *y, double *zx, double *zy)
{
	double	x_f	   = 0;
	double	dx_f	   = 0;
	double wdx_f      = 0;
	double wddx_f     = 0;
	double	y_f	   = 0;
	double	dy_f	   = 0;
	double wdy_f      = 0;
	double wddy_f     = 0;
	double sup = (this)->Tsup;
	double sx = nextsx;
	(this)->nextsx = (this)->sx;
	double sy = 0.11;
	double sohen_endx0 = 0;
	double sohen_endy0 = 0;
	double	sohen_endx = 0;
	double	sohen_endy = 0;
	double	v_x	   = 0;
	double	v_y	   = 0;
	double	mokuhyo_x  = 0;
	double	mokuhyo_dx = 0;
	double	mokuhyo_y  = 0;
	double	mokuhyo_dy = 0;
	beforetheta = theta;
	theta = nexttheta;
  //左右のどちらへ移動する
  //sidesy > 0 左移動
  //sidesy < 0 右移動
	int lf = (sidesy > 0) ? 0 : 1;
	if(n % 2 == lf){
	  	sy += fabs(sidesy);
	}
	double	a = 10,b=1;
	TC  = sqrt(zc/g);
	C   = cosh(sup/TC);
	S   = sinh(sup/TC);
	D   = a*(C-1)*(C-1)+b*(S/TC)*(S/TC);
  
	new_p_x_1 = new_p_x;
	new_p_y_1 = new_p_y;
	x_f_2 = x_f_1;
	y_f_2 = y_f_1;
	dx_f_2 = dx_f_1;
	dy_f_2 = dy_f_1;

  
	x_f  = (x_f_1-new_p_x)*C+TC*dx_f_1*S+new_p_x;	//式4.54
	dx_f = ((x_f_1-new_p_x)/TC)*S+dx_f_1*C;	//式4.54
	y_f  = (y_f_1-new_p_y)*C+TC*dy_f_1*S+new_p_y;	//式4.54
	dy_f = ((y_f_1-new_p_y)/TC)*S+dy_f_1*C;	//式4.54
	
	
  
//	  p_x = p_x_1 + sx*cos(theta) + sign*sy*sin(theta);		//4.48 sx=歩幅(停止するときはここに0が入る) 
//	  p_y = p_y_1 + sx*sin(theta) - sign*sy*cos(theta);	//4.48 純粋に歩幅からもとめた着地位置
	p_x = p_x_1 + sx;		//4.48 sx=歩幅(停止するときはここに0が入る) 
	p_y = p_y_1 - sign*sy;	//4.48 純粋に歩幅からもとめた着地位置
	sohen_endx0 = ((this)->nextsx)/2;
	double sidesy = fabs((this)->sidesy);
	if(!(n % 2 == lf)){//支持脚を踏まないようにする
		sohen_endy0 = (sign*(sy+sidesy)/2);	//回転前
	}else{
		sohen_endy0 =(sign*(sy-sidesy)/2);//回転前
	}
		//座標変換処理
//		sohen_endx = sohen_endx0*cos(nexttheta) - sohen_endy0*sin(nexttheta);
//		sohen_endy = sohen_endx0*sin(nexttheta) + sohen_endy0*cos(nexttheta);
	sohen_endx = sohen_endx0;
	sohen_endy = sohen_endy0;
	
//	  v_x = ( (C+1)/(TC*S)*sohen_endx0 * cos(nexttheta) )- ( (C-1)/(TC*S)*sohen_endy0 * sin(nexttheta));	// v_x=歩行素片の終端速度
//	  v_y = ( (C+1)/(TC*S)*sohen_endx0 * sin(nexttheta) )+ ( (C-1)/(TC*S)*sohen_endy0 * cos(nexttheta));	//
	v_x = ( (C+1)/(TC*S)*sohen_endx0);	// v_x=歩行素片の終端速度
	v_y = ( (C-1)/(TC*S)*sohen_endy0);
	mokuhyo_x  = p_x+sohen_endx;
	mokuhyo_dx = v_x;
	mokuhyo_y  = p_y+sohen_endy;
	mokuhyo_dy = v_y;
	
	if(doublesupportflag){//両脚支持を行う時
		g_ax0 = x_f;
		g_ay0 = y_f;
		g_ax1 = dx_f;//t:0のときの速度
		g_ay1 = dy_f;
		g_ax2 = ((g/zc)*(x_f-new_p_x))/2;//t:0のときの加速度
		g_ay2 = ((g/zc)*(y_f-new_p_y))/2;
		new_p_x = -((a*(C-1))/D)*(mokuhyo_x-C*x_f-TC*S*dx_f)
	  	          -((b*S)/(TC*D))*(mokuhyo_dx-(S/TC)*x_f-C*dx_f);
	  	new_p_y = -(a*(C-1)/D)*(mokuhyo_y-C*y_f-TC*S*dy_f)
	  	          -((b*S)/(TC*D))*(mokuhyo_dy-(S/TC)*y_f-C*dy_f);
		
		wdx_f	 = dx_f;//両足支持をしたときのdbl後の速度
		wddx_f = ((g/zc)*(x_f-new_p_x));//dbl後の加速度
		wdy_f	 = dy_f;
		wddy_f = ((g/zc)*(y_f-new_p_y));
	
		double ax[2][2] = {{3*pow(dbl,2),4*pow(dbl,3)},{6*dbl,12*pow(dbl,2)}};
		double bx[2]    = {wdx_f-g_ax1-2*g_ax2*dbl, wddx_f-2*g_ax2};
		Gauss_J(2,(double *)ax,(double *)bx);
		double ay[2][2] = {{3*pow(dbl,2),4*pow(dbl,3)},{6*dbl,12*pow(dbl,2)}};
		double by[2]    = {wdy_f-g_ay1-2*g_ay2*dbl,wddy_f-2*g_ay2};
		Gauss_J(2,(double *)ay,(double *)by);
	
		g_ax3 = bx[0];
		g_ay3 = by[0];
		g_ax4 = bx[1];
		g_ay4 = by[1];
		x_f_1	  = g_ax0+g_ax1*dbl+g_ax2*pow(dbl,2)+g_ax3*pow(dbl,3)+g_ax4*pow(dbl,4);
		y_f_1	  = g_ay0+g_ay1*dbl+g_ay2*pow(dbl,2)+g_ay3*pow(dbl,3)+g_ay4*pow(dbl,4);
		new_p_x += g_ax1*dbl+g_ax2*pow(dbl,2)+g_ax3*pow(dbl,3)+g_ax4*pow(dbl,4);
		new_p_y += g_ay1*dbl+g_ay2*pow(dbl,2)+g_ay3*pow(dbl,3)+g_ay4*pow(dbl,4);
		new_x_dt = g_ax1*dbl+g_ax2*pow(dbl,2)+g_ax3*pow(dbl,3)+g_ax4*pow(dbl,4);
		new_y_dt = g_ay1*dbl+g_ay2*pow(dbl,2)+g_ay3*pow(dbl,3)+g_ay4*pow(dbl,4);
	}else{//行わない場合
		x_f_1	  = x_f;
		y_f_1   = y_f;
		new_p_x = -(a*(C-1)/D)*(mokuhyo_x-C*x_f-TC*S*dx_f)
	  	          -((b*S)/(TC*D))*(mokuhyo_dx-(S/TC)*x_f-C*dx_f);

		new_p_y = -(a*(C-1)/D)*(mokuhyo_y-C*y_f-TC*S*dy_f)
	  	          -((b*S)/(TC*D))*(mokuhyo_dy-(S/TC)*y_f-C*dy_f);
	}	
	/****前回の情報を保存*****/
	dx_f_1  = dx_f;
	dy_f_1  = dy_f;
	p_x_1	  = p_x;
	p_y_1	  = p_y;
	sign	 *= -1;
	/**********************/  
	  
	*x  = new_p_x;
	*y  = new_p_y;
	*zx = x_f;
	*zy = y_f;
	//歩数追加
	n++;
}
