// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#ifndef __MAKEWALK_H__
#define __MAKEWALK_H__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <map>
#include <string>
// #include <Eigen/Core>


class MakeWalk
{	
	public:
		MakeWalk();//コンストラクタ
	private:
	//非公開定数
	const double SIMGAIN;
	const double UPPERLEG;
	const double LOWERLEG;
	const double ANCLEFOOT;
	const double FOOTX;
	const double MAXSPEED;
	const double DEGTORAD;
	const double RADTODEG;
	const double OFFSET;
	const double ANKLE_OFFSET;
	const double TOELENGTH;
	const double HEELLENGTH;
	const double FOOTSIDELENGTH;
	const double ANKLETOFOOT;
	//非公開変数
	double rpos[3];//右脚目標座標位置
	double lpos[3];//左脚目標座標位置
	double brpos[3];//一つ手前のステートの右脚座標位置
	double blpos[3];//一つ手前のステートの左脚座標位置
	double rangle[7];//右脚の目標関節角度
	double langle[7];//左脚の目標関節角度
	int state;//歩行の状態
	double n_rangle[7];//現在の右脚関節角度
	double n_langle[7];//現在の左脚関節角度
	double brangle[7];//一つ前の関節角度
	double blangle[7];//一つ前の関節角度
	double Tsup;//周期(上げ下ろし間)
	double nextstatetime;//次のステートへの移行時間
	double nextsuptime;//次の周期
	double legheight;//胴体座標系での足のz位置
	double upleg;//脚をあげる高さ
	double sx;//前後への移動量
	double sidesy;//左右への移動量
	double sr;//左右の回転量
	double nextsx; //次の前後への移動量
	double nextsy; //次の左右への移動量
	double x;//モデル上のx
	double y;//モデル上のy
	double theta;//ロボットの向き
	double beforetheta;//一つ前のロボットの向き
	double nexttheta;//要求するロボットの向き
	double left_yaw;//ヨー軸の変化量
	double right_yaw;//ヨー軸の変化量
	double maxdist;//ロボットが踏み出せる最大の長さ
	int onx;//歩幅を増やしてもいい場合1になる
	int ony;//歩幅を増やしてもいい場合1になる
	int onr;//回転してもいい場合1になる 
  
	
	double rvelocity[7];//速度命令
	double lvelocity[7];//速度命令
  
  	//倒立振子系
	double x_f_1;
	double dx_f_1;
	double y_f_1;
	double dy_f_1;
	double new_p_x;
	double new_p_x_1;
	double new_p_y;
	double new_p_y_1;
	double new_x_dt;
	double new_y_dt;
	double	p_x;
	double	p_y;
	double p_x_1;
	double p_y_1;
	double x_f_2;
	double y_f_2;
	double dx_f_2;
	double dy_f_2;
	double x_f2;
	double y_f2;
	double dx_f2;
	double dy_f2;
	
	double g_ax0;
	double g_ax1;
	double g_ax2;
	double g_ax3;
	double g_ax4;
	double g_ay0;
	double g_ay1;
	double g_ay2;
	double g_ay3;
	double g_ay4;
	double dbl;
	double dblhalf;
	
	double TC;
	double C;
	double S;
	double D;
	double zc;
	double g;

	int n;
	int sign;
	double t;
  
	double rx;
	double ry;
	double rzx;
	double rzy;
	double bx;
	double by;
	double bbx;
	double bby;


	//PID  
	double i_rangle[7];
	double i_langle[7];
	double d_rdiff[7];
	double d_ldiff[7];
	double pre_t_rangle[7];
	double pre_t_langle[7];
	double pre_n_rangle[7];
	double pre_n_langle[7];

	//踵接地・爪先離陸関係
	double landingpoints;//次の着地位置(胴体座標系)
	double heeltime;//踵接地時間
	double toetime;//爪先離陸時間
	double dblheeltime;//両脚支持期間中の踵接地時間
	double dbltoetime;//両脚支持期間中の爪先離陸時間
	double toeangle;//爪先角度
	double heelangle;//踵角度
	double footsideangle;//足首ロール角度
	double r_toeangle;//右爪先角度
	double l_toeangle;//左爪先角度
	double br_toeangle;//一つ前の爪先角度
	double bl_toeangle;//一つ前の爪先角度
	
  
	bool doublesupportflag;//両脚支持期間を設けるか否か
	bool startflag;			//最初の両脚支持期間の計算用
	bool rotationchange; //回転を変更するかしないか
	bool toestrike;//爪先接地

	double STATEDIFF;//280msの時、0.04がベスト. 240,200msの時、0.02がベスト 160msの時0.00がベスト
	
	//非公開関数
	private:
	void transpointX(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c);
	void transpointY(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c);
	void transpointZ(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c);
	void Gauss_J( int n, double *a, double *b);
	void JointUpdate(double joint[]);
	void COMCalculation(double time);
	void DoubleSupport(double dbltime);
	void RoboCalcPendulum(double *x, double *y, double *zx, double *zy);	
	void CheckLimit(double rangle[], double langle[]);
	void AngleTrajectory(double time, double time2, double nset[], double dset[]);
	void setHeelToe(double rangle[], double langle[]);
	void setYawAngle();
	void setAnklePos();
	void HeelAngle(double time, double pos[]);
	void ToeAngle(double time, double pos[]);
	void coordinateConverter(double v[]);
	void timeupdate();
	void OutputCommand(double velocity[]);
	void LegVelocity(double angle[], double velocity[], bool velocityCheck);
	void OldLegVelocity(double angle[], double velocity[]);
	void LegTrajectory(double time,double time2, double dpos[],double npos[],double rpos[]);
	void update(double joint[], double velocity[], double walkx, double walky, double rotation, bool act);
	public:
	
	void RightLegIK(double target_angle[], double target_point[], double yaw);
	void LeftLegIK(double target_angle[], double target_point[], double yaw);
	void init();
	void quickinit(double lanklepos[],double ranklepos[]);
	// void quickinit(Eigen::Vector3d l, Eigen::Vector3d r);
	//ゲット系
	void getlegpos(double r[],double l[]);
	double getTsup();
	double getlegheight();
	int getStepCount();
	//セット系
	void setTsup(double param);
	void setdbl(double param);
	void setzc(double param);
	void setupleg(double param);
	void setdblflag(bool param);
	
	bool WalkControl(double joint[], double velocity[],
	double walkx, double walky, double rotation, bool act);

};

#endif
