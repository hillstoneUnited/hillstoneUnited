#include "odenswalk.hpp"

OdensWalk::OdensWalk(double _dest[]){
    finish_flag = false;
    dest[0] = _dest[0];
    dest[1] = _dest[1];
}

OdensWalk::~OdensWalk(){}

std::string OdensWalk::getNextAngle(World& w){
    resetAngleMap();

    //MakeWalkの戻り値を受け取る
    bool isWalking;
    //前方方向の歩幅
    double step_x = 0;
    //左右方向の歩幅(左が正)
    double step_y = 0;
    //目標の向きとの角度差[rad]
    double rotation = 0;
    //歩行信号
    //trueの場合のみ歩行する
    //falseになると、両足が着いたタイミングで停止する
    bool act = true;
    
    //ボールの情報から、歩幅を決定する
    const double MAX_STEP_X = 0.09;//前後の最大歩幅
    const double MAX_STEP_Y = 0.03;//左右の最大歩幅
    const double MAX_STEP_R = 30*M_PI/180;//旋回の最大角度
    
    //TODO: check which x or y is infront and behind
    //now set x as zengo
    //calculate rotation from mypos and goal
    double mypos[2] = {};
    for (int i = 0; i < 2; i++)
    {
        mypos[i] = w.getMYPOS(i);
    }
    rotation = atan2(dest[0]-mypos[0], dest[1]-mypos[1]) - w.getABSANGLE();
    
    //最大値を超えないようにする
    if(rotation > MAX_STEP_R){
        rotation = MAX_STEP_R;
    }else if(rotation < -MAX_STEP_R){
        rotation = -MAX_STEP_R;
    }

    if(fabs(rotation) > 10*M_PI/180)
    {
        //角度が大きい場合はその場旋回
        step_x = 0;
        step_y = 0;
    }else{
        //ODENSの座標系に合わせて計算
        step_x = dest[0];
        step_y = dest[1];
        //最大値を超えないようにする
        if(step_x > MAX_STEP_X){
            step_x = MAX_STEP_X;
        }else if( step_x < -MAX_STEP_X){
            step_x = -MAX_STEP_X;
        }
        if(step_y > MAX_STEP_Y){
            step_y = MAX_STEP_Y;
        }else if( step_y < -MAX_STEP_Y){
            step_y = -MAX_STEP_Y;
        } 
    }
    
    //現在の関節角度の取得
    //左脚第一関節から順番に定義されている
    joint[0] = w.getAngle("llj1");
    joint[1] = w.getAngle("llj2");
    joint[2] = w.getAngle("llj3");
    joint[3] = w.getAngle("llj4");
    joint[4] = w.getAngle("llj5");
    joint[5] = w.getAngle("llj6");

    joint[6] = w.getAngle("rlj1");
    joint[7] = w.getAngle("rlj2");
    joint[8] = w.getAngle("rlj3");
    joint[9] = w.getAngle("rlj4");
    joint[10] = w.getAngle("rlj5");
    joint[11] = w.getAngle("rlj6");

    //MakeWalkを用いて、関節動作を決定する
    //計算結果はvelocityに代入される
    isWalking = mw.WalkControl(joint, step_x, step_y, rotation, act);
    //resultがtrueの時、歩行動作中である
    if(isWalking){
        std::cout << "Walking!\n";
        finish_flag = false;
    }else{
        std::cout << "Stopping!\n";
        finish_flag = true;
    }

    setAngle(w, joint);

    return angleToString();

}


void OdensWalk::setAngle(World& w, double joint[]){

  /** Left **/
  //Legs
  set(w, llj1, joint[0]);
  set(w, llj2, joint[1]);
  set(w, llj3, joint[2]);
  set(w, llj4, joint[3]);
  set(w, llj5, joint[4]);
  set(w, llj6, joint[5]);

  /** Right **/
  //Legs
  set(w, rlj1, joint[6]);
  set(w, rlj2, joint[7]);
  set(w, rlj3, joint[8]);
  set(w, rlj4, joint[9]);
  set(w, rlj5, joint[10]);
  set(w, rlj6, joint[11]);

}