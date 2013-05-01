#include "odenswalk.hpp"
#include <stdio.h>

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
        mypos[i] = w.getXY(i);
    }
    rotation = atan2(dest[1]-mypos[1], dest[0]-mypos[0]) - w.getABSANGLE();
    
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
        step_x = dest[0] - mypos[0];
        step_y = dest[1] - mypos[1];
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
    joint[0] = w.getAngle("llj1") * DEGTORAD;
    joint[1] = w.getAngle("llj2") * DEGTORAD;
    joint[2] = w.getAngle("llj3") * DEGTORAD;
    joint[3] = w.getAngle("llj4") * DEGTORAD;
    joint[4] = w.getAngle("llj5") * DEGTORAD;
    joint[5] = w.getAngle("llj6") * DEGTORAD;

    joint[6] = w.getAngle("rlj1") * DEGTORAD;
    joint[7] = w.getAngle("rlj2") * DEGTORAD;
    joint[8] = w.getAngle("rlj3") * DEGTORAD;
    joint[9] = w.getAngle("rlj4") * DEGTORAD;
    joint[10] = w.getAngle("rlj5") * DEGTORAD;
    joint[11] = w.getAngle("rlj6") * DEGTORAD;


    double velocity[12] = {};
    //MakeWalkを用いて、関節動作を決定する
    //計算結果はvelocityに代入される
    isWalking = mw.WalkControl(joint, velocity, step_x, step_y, rotation, act);
    //resultがtrueの時、歩行動作中である
    if(isWalking){
        std::cout << "Walking!\n";
        finish_flag = false;
    }else{
        std::cout << "Stopping!\n";
        finish_flag = true;
    }

    setAngle(w, joint, velocity);
    // setAngle(w, joint);

    /**for debagging**/
    std::cout << "runto:" << dest[0] << "," << dest[1] << std::endl;
    std::cout << "mypos:" << mypos[0] << "," << mypos[1] << std::endl;

    return angleToString();

}


bool OdensWalk::set(jointID id, double velocity){
  const double EPS = 0.2; // just like margin of error
  double current = 0.0;

  angleMap[id] = velocity;
  return true;
}

bool OdensWalk::set(World& w, jointID id, 
    double angle, double gain){
  const double EPS = 0.2; // just like margin of error
  double current = 0.0;

  switch(id){
    case hj1: current = w.getAngle("hj1");break;
    case hj2: current = w.getAngle("hj2");break;
    case laj1: current = w.getAngle("laj1");break;
    case raj1: current = w.getAngle("raj1");break;
    case laj2: current = w.getAngle("laj2");break;
    case raj2: current = w.getAngle("raj2");break;
    case laj3: current = w.getAngle("laj3");break;
    case raj3: current = w.getAngle("raj3");break;
    case laj4: current = w.getAngle("laj4");break;
    case raj4: current = w.getAngle("raj4");break;
    case llj1: current = w.getAngle("llj1");break;
    case rlj1: current = w.getAngle("rlj1");break;
    case llj2: current = w.getAngle("llj2");break;
    case rlj2: current = w.getAngle("rlj2");break;
    case llj3: current = w.getAngle("llj3");break;
    case rlj3: current = w.getAngle("rlj3");break;
    case llj4: current = w.getAngle("llj4");break;
    case rlj4: current = w.getAngle("rlj4");break;
    case llj5: current = w.getAngle("llj5");break;
    case rlj5: current = w.getAngle("rlj5");break;
    case llj6: current = w.getAngle("llj6");break;
    case rlj6: current = w.getAngle("rlj6");break;
    default:
      std::cout << "Cannot find ID : " << id << std::endl;
      break;
  }

  if(fabs(current - angle) > EPS){
    angleMap[id] = gain * (angle - current);
    return true;
  }

  angleMap[id] = 0.0;
  return false;
}


void OdensWalk::setAngle(World& w, double joint[]){

    double joint_set[12] = {};

    for (int i = 0; i < 12; i++)
    {
        joint_set[i] = joint[i];
    }

    double gain = 0.5;
    
    // Left
    // Legs
    set(w, llj1, joint_set[0], gain);
    set(w, llj2, joint_set[1], gain);
    set(w, llj3, joint_set[2], gain);
    set(w, llj4, joint_set[3], gain);
    set(w, llj5, joint_set[4], gain);
    set(w, llj6, joint_set[5], gain);

    // Right
    // Legs
    set(w, rlj1, joint_set[6], gain);
    set(w, rlj2, joint_set[7], gain);
    set(w, rlj3, joint_set[8], gain);
    set(w, rlj4, joint_set[9], gain);
    set(w, rlj5, joint_set[10], gain);
    set(w, rlj6, joint_set[11], gain);

}


void OdensWalk::setAngle(World& w, double joint[], double velocity[]){

    double gain = 100;
    double joint_set[12] = {};

    for (int i = 0; i < 12; i++)
    {
        joint_set[i] = joint[i];
    }

    // Left
    // Legs
    set(llj1, velocity[0] * gain);
    set(llj2, velocity[1] * gain);
    set(llj3, -velocity[2] * gain);
    set(llj4, -velocity[3] * gain);
    set(llj5, -velocity[4] * gain);
    set(llj6, velocity[5] * gain);

    // Right
    // Legs
    set(rlj1, velocity[6] * gain);
    set(rlj2, velocity[7] * gain);
    set(rlj3, -velocity[8] * gain);
    set(rlj4, -velocity[9] * gain);
    set(rlj5, -velocity[10] * gain);
    set(rlj6, velocity[11] * gain); 
    
}
