// Copyright (c) 2012 Team ODENS,
// Masutani Lab., Osaka Electro-Communication University
// Author: Takuya Maruyama
// Date:   2012/09/07

#include"./makewalk.hpp"

//歩幅を設定する
//act :　歩容を更新する
bool MakeWalk::WalkControl(double joint[],double velocity[], double walkx, double walky, double rotation, bool act)
{
	//停止信号
	if(act == 0 && (t > nextstatetime) && (state == 4 || state == 1 || state == -2)){
		return 0;
	}
	//歩容の更新
	(this)->update(joint, velocity,walkx,walky,rotation, act);
	return 1;
}
