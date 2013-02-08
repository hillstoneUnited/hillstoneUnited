// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"./makewalk.hpp"

//キック等を行い、腰を屈めた状態からの初期化
void MakeWalk::quickinit(double lanklepos[],double ranklepos[])
{
	init();
	nextstatetime = 0.4;
	nextsuptime = 0.4;
	//ODENS形式の座標系に変換
	coordinateConverter(lanklepos);
	coordinateConverter(ranklepos);
	//過去の足首位置を更新する
	brpos[1] = rpos[1] = ranklepos[1];
	blpos[1] = lpos[1] = lanklepos[1];
	brpos[0] = rpos[0] = ranklepos[0];
	blpos[0] = lpos[0] = lanklepos[0];
	brpos[2] = rpos[2] = ranklepos[2];
	blpos[2] = lpos[2] = lanklepos[2];
}

/*
//libbats用にEigenでも受け取れるようにしている
void MakeWalk::quickinit(Eigen::Vector3d l,Eigen::Vector3d r)
{
	init();
	nextstatetime = 0.4;
	nextsuptime = 0.4;
	double lanklepos[3] = {l[0], l[1], l[2]};
	double ranklepos[3] = {r[0], r[1], r[2]};
	//ODENS形式の座標系に変換
	coordinateConverter(lanklepos);
	coordinateConverter(ranklepos);
	//過去の足首位置を更新する
	brpos[1] = rpos[1] = ranklepos[1];
	blpos[1] = lpos[1] = lanklepos[1];
	brpos[0] = rpos[0] = ranklepos[0];
	blpos[0] = lpos[0] = lanklepos[0];
	brpos[2] = rpos[2] = ranklepos[2];
	blpos[2] = lpos[2] = lanklepos[2];
}
*/
