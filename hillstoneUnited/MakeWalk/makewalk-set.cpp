// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07
	
#include "makewalk.hpp"

/*----------------------------------------------------
	セット関数系	
------------------------------------------------------*/
//周期のパラメータを変更する
void MakeWalk::setTsup(double param)
{
	if(param == 0 || ((this)->state != 3 && (this)->state != -2 )){
		return;
	}
	(this)->Tsup = param;
  TC  = sqrt(zc/g);
  C   = cosh(Tsup/TC);
  S   = sinh(Tsup/TC);
}
//両脚支持期間のパラメータを変更する
void MakeWalk::setdbl(double param)
{
	if(param == 0  || ((this)->state != 3 && (this)->state != -2 )){
		return;
	}
	(this)->dbl = param;
}
//重心の高さのパラメータを変更する
void MakeWalk::setzc(double param)
{
	(this)->zc = param;
	TC  = sqrt(zc/g);
	C   = cosh(Tsup/TC);
	S   = sinh(Tsup/TC);
}
//足を上げる高さのパラメータを変更する
void MakeWalk::setupleg(double param)
{
	if(param == 0  || ((this)->state != 3 && (this)->state != -2 )){
		return;
	}
	(this)->upleg = param;
}
//両脚支持期間を行うか変更する
void MakeWalk::setdblflag(bool param)
{
	if(((this)->state != 3 && (this)->state != -2 )){
		return;
	}
	(this)->doublesupportflag = (bool)param;
}
	
//get系関数
double MakeWalk::getlegheight(){
	return (this)->legheight;
}
void MakeWalk::getlegpos(double r[],double l[]){
	r[0] = rpos[0];
	r[1] = rpos[1];
	r[2] = rpos[2];
	l[0] = lpos[0];
	l[1] = lpos[1];
	l[2] = lpos[2];
}
int MakeWalk::getStepCount(){
	return n;
}

double MakeWalk::getTsup(){
	return Tsup;
}
