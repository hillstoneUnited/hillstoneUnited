// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"makewalk.hpp"
void  MakeWalk::transpointX(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c){
	boost::numeric::ublas::matrix<double> tp(4,4);
	tp(0,0) = 1; tp(0,1) = 0; tp(0,2) = 0;		tp(0,3) = move(0);// 1 0 0 0
	tp(1,0) = 0; tp(1,1) = c; tp(1,2) = -1*s;	tp(1,3) = move(1);// 0 c-s 0
	tp(2,0) = 0; tp(2,1) = s; tp(2,2) = c;		tp(2,3) = move(2);// 0 s c 0
	tp(3,0) = 0; tp(3,1) = 0; tp(3,2) = 0;		tp(3,3) = 1;      // 0 0 0 1

	bb = prod(bb, tp);
}

void  MakeWalk::transpointY(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c){
	boost::numeric::ublas::matrix<double> tp(4,4);
	tp(0,0) = c;	tp(0,1) = 0; tp(0,2) = s; tp(0,3) = move(0);// c 0 s 0
	tp(1,0) = 0;	tp(1,1) = 1; tp(1,2) = 0; tp(1,3) = move(1);// 0 1 0 0
	tp(2,0) = -1*s; tp(2,1) = 0; tp(2,2) = c; tp(2,3) = move(2);//-s 0 c 0
	tp(3,0) = 0;	tp(3,1) = 0; tp(3,2) = 0; tp(3,3) = 1;      // 0 0 0 1

	bb = prod(bb, tp);
}
void  MakeWalk::transpointZ(boost::numeric::ublas::matrix<double> &bb, boost::numeric::ublas::vector<double> move, double s, double c){

	boost::numeric::ublas::matrix<double> tp(4,4);
	tp(0,0) = c; tp(0,1) = -1*s; tp(0,2) = 0; tp(0,3) = move(0);
	tp(1,0) = s; tp(1,1) = c;	 tp(1,2) = 0; tp(1,3) = move(1);
	tp(2,0) = 0; tp(2,1) = 0;	 tp(2,2) = 1; tp(2,3) = move(2);
	tp(3,0) = 0; tp(3,1) = 0;	 tp(3,2) = 0; tp(3,3) = 1;

	bb = prod(bb, tp);
}


/*--------------------------------------------------------------------------------*/
//逆運動学計算
//double tangle[] 逆運動学の計算結果が代入される
//double target_point 胴体座標系における目標の足首座標
//double yaw yaw軸の角度[degree]
/*--------------------------------------------------------------------------------*/	
void  MakeWalk::LeftLegIK(double tangle[], double target_point[], double yaw = 0){
	boost::numeric::ublas::vector<double> smove(4);//init
	smove(0) = 0; smove(1) = 0; smove(2) = 0; smove(3) = 1;
	boost::numeric::ublas::matrix<double> R1(4,4);
	R1(0,0) = 1; R1(0,1) = 0; R1(0,2) = 0; R1(0,3) = 0;
	R1(1,0) = 0; R1(1,1) = 1; R1(1,2) = 0; R1(1,3) = 0;
	R1(2,0) = 0; R1(2,1) = 0; R1(2,2) = 1; R1(2,3) = 0;
	R1(3,0) = 0; R1(3,1) = 0; R1(3,2) = 0; R1(3,3) = 1;
	boost::numeric::ublas::matrix<double> BF = R1;
	boost::numeric::ublas::matrix<double> RS = R1;//init
	boost::numeric::ublas::matrix<double> Ra = R1;
	boost::numeric::ublas::matrix<double> Rtmp = R1;
/*
	Eigen::Vector3d smove;
	smove[0] = 0; smove[1] = 0; smove[2] = 0;
	Eigen::Transform3d R1;
	R1.matrix() = Eigen::MatrixXd::Identity(4, 4);
	Eigen::Transform3d BF;
	BF.matrix() = Eigen::MatrixXd::Identity(4, 4);
	Eigen::Transform3d RS;
	RS.matrix() = Eigen::MatrixXd::Identity(4, 4);
	Eigen::Transform3d Ra;
	Ra.matrix() = Eigen::MatrixXd::Identity(4, 4);
	Eigen::Transform3d Rtmp;
	Rtmp.matrix() = Eigen::MatrixXd::Identity(4, 4);
*/

	double lj1plusangle = 45.0;//脚付け根の傾き
	double torso[3] = {0,0,0};//胴体位置
	double lhip[3] = {-0.055, -0.01, -0.115};
	if(tangle[0] == -1){
		//legL
		lj1plusangle = -1*lj1plusangle;
		if(yaw < 0){
			yaw = 0;
		}
	}else if(tangle[0] == 1){
		//legR
			if(yaw > 0){
				yaw = 0;
			}
	}else{
		//bad
	}
	//以下、計算部
	double C2 = ((lhip[0]-target_point[0])*(lhip[0]-target_point[0]))+((lhip[1]-target_point[1])*(lhip[1]-target_point[1]))+((lhip[2]-target_point[2])*(lhip[2]-target_point[2]));
	if(sqrt(C2) > 0.220){
		C2 = 0.220*0.220;
	}
	tangle[4] = (acos(((UPPERLEG*UPPERLEG)+(LOWERLEG*LOWERLEG)-C2)/(2*UPPERLEG*LOWERLEG))*(180.0/M_PI))-180.0;

	double alpha = acos((C2+(LOWERLEG*LOWERLEG)-(UPPERLEG*UPPERLEG))/(2*sqrt(C2)*LOWERLEG));

	tangle[6] = -1*atan2(-1*(target_point[0]-lhip[0]), -1*(target_point[2]-lhip[2]))*180.0/M_PI;

	int pm;
	if(-1*(target_point[2]-lhip[2]) >= 0){
		pm = 1;
	}else{
		pm = -1;
	}
	tangle[5] = -1*(-atan2(lhip[1]-target_point[1], pm*sqrt((lhip[0]-target_point[0])*(lhip[0]-target_point[0])+(lhip[2]-target_point[2])*(lhip[2]-target_point[2])))-alpha)*180.0/M_PI;
	
	//yaw = yaw * M_M_PI / 180;
	transpointY(R1, smove, sin(lj1plusangle*M_PI/180.0), cos(lj1plusangle*M_PI/180.0));
	transpointZ(R1,smove, sin(yaw),cos(yaw));
	//R1 = prod(Rtmp, trans(R1));

	Ra = prod(R1, Ra);
	Rtmp = RS;
	transpointY(Rtmp, smove, sin(tangle[6]*M_PI/180.0), cos(tangle[6]*M_PI/180.0));
	Ra = prod(Ra, trans(Rtmp));
	Rtmp = RS;
	transpointX(Rtmp, smove, sin((tangle[4]+tangle[5])*M_PI/180.0), cos((tangle[4]+tangle[5])*M_PI/180.0));
	Ra = prod(Ra, trans(Rtmp));
	
	if(tangle[0] == 1){//right
		tangle[1] =-(atan2(-Ra(1,0),Ra(0,0))*(180.0/M_PI));
	}else{//left
		tangle[1] = (atan2(-Ra(1,0),Ra(0,0))*(180.0/M_PI));
	}
	tangle[3] = atan2(Ra(2,1),Ra(2,2))*180.0/M_PI;
	tangle[2] = atan2(-1*Ra(2,0)*sin(tangle[3]*M_PI/180.0),Ra(2,1))*180.0/M_PI-lj1plusangle;
	if(tangle[2] > 90){
		tangle[2] -= 180;
	}else if(tangle[2] < -90){
    tangle[2] += 180;
  }
	tangle[3]-= OFFSET;
	tangle[4]+= OFFSET;
}
/*--------------------------------------------------------------------------------*/
//逆運動学計算
//double tangle[] 逆運動学の計算結果が代入される
//double target_point 胴体座標系における目標の足首座標
//double yaw yaw軸の角度[degree]
/*--------------------------------------------------------------------------------*/	
void  MakeWalk::RightLegIK(double tangle[], double target_point[], double yaw = 0){
	boost::numeric::ublas::vector<double> smove(4);//init
	smove(0) = 0; smove(1) = 0; smove(2) = 0; smove(3) = 1;
	boost::numeric::ublas::matrix<double> R1(4,4);
	R1(0,0) = 1; R1(0,1) = 0; R1(0,2) = 0; R1(0,3) = 0;
	R1(1,0) = 0; R1(1,1) = 1; R1(1,2) = 0; R1(1,3) = 0;
	R1(2,0) = 0; R1(2,1) = 0; R1(2,2) = 1; R1(2,3) = 0;
	R1(3,0) = 0; R1(3,1) = 0; R1(3,2) = 0; R1(3,3) = 1;
	boost::numeric::ublas::matrix<double> BF = R1;
	boost::numeric::ublas::matrix<double> RS = R1;//init
	boost::numeric::ublas::matrix<double> Ra = R1;
	boost::numeric::ublas::matrix<double> Rtmp = R1;


	double lj1plusangle = 45.0;//脚付け根の傾き
	double torso[3] = {0,0,0};//胴体位置
	double rhip[3] = {0.055, -0.01, -0.115};
	if(tangle[0] == -1){
		//legL
		lj1plusangle = -1*lj1plusangle;
		if(yaw < 0){
			yaw = 0;
		}
	}else if(tangle[0] == 1){
		//legR
			if(yaw > 0){
				yaw = 0;
			}
	}else{
		//bad
	}
	//以下、計算部
	double C2 = ((rhip[0]-target_point[0])*(rhip[0]-target_point[0]))+((rhip[1]-target_point[1])*(rhip[1]-target_point[1]))+((rhip[2]-target_point[2])*(rhip[2]-target_point[2]));
	if(sqrt(C2) > 0.220){
		C2 = 0.220*0.220;
	}
	tangle[4] = (acos(((UPPERLEG*UPPERLEG)+(LOWERLEG*LOWERLEG)-C2)/(2*UPPERLEG*LOWERLEG))*(180.0/M_PI))-180.0;

	double alpha = acos((C2+(LOWERLEG*LOWERLEG)-(UPPERLEG*UPPERLEG))/(2*sqrt(C2)*LOWERLEG));

	tangle[6] = -1*atan2(-1*(target_point[0]-rhip[0]), -1*(target_point[2]-rhip[2]))*180.0/M_PI;

	int pm;
	if(-1*(target_point[2]-rhip[2]) >= 0){
		pm = 1;
	}else{
		pm = -1;
	}
	tangle[5] = -1*(-atan2(rhip[1]-target_point[1], pm*sqrt((rhip[0]-target_point[0])*(rhip[0]-target_point[0])+(rhip[2]-target_point[2])*(rhip[2]-target_point[2])))-alpha)*180.0/M_PI;
	Rtmp = RS;
	
	//yaw = yaw * M_M_PI / 180;
	transpointY(R1, smove, sin(lj1plusangle*M_PI/180.0), cos(lj1plusangle*M_PI/180.0));
	transpointZ(R1,smove, sin(yaw),cos(yaw));
	//R1 = prod(Rtmp, trans(R1));

	Ra = prod(R1, Ra);
	Rtmp = RS;
	transpointY(Rtmp, smove, sin(tangle[6]*M_PI/180.0), cos(tangle[6]*M_PI/180.0));
	Ra = prod(Ra, trans(Rtmp));
	Rtmp = RS;
	transpointX(Rtmp, smove, sin((tangle[4]+tangle[5])*M_PI/180.0), cos((tangle[4]+tangle[5])*M_PI/180.0));
	Ra = prod(Ra, trans(Rtmp));
	
	if(tangle[0] == 1){//right
		tangle[1] =-(atan2(-Ra(1,0),Ra(0,0))*(180.0/M_PI));
	}else{//left
		tangle[1] = (atan2(-Ra(1,0),Ra(0,0))*(180.0/M_PI));
	}
	tangle[3] = atan2(Ra(2,1),Ra(2,2))*180.0/M_PI;
	tangle[2] = atan2(-1*Ra(2,0)*sin(tangle[3]*M_PI/180.0),Ra(2,1))*180.0/M_PI-lj1plusangle;
	if(tangle[2] > 90){
		tangle[2] -= 180;
	}else if(tangle[2] < -90){
    tangle[2] += 180;
  }
	tangle[3]-= OFFSET;
	tangle[4]+= OFFSET;
	
}
