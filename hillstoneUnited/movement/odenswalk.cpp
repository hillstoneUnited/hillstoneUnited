#include "odenswalk.hpp"

// x: distance to ball (zengo soutai)
// y: distance to ball (sayu soutai)

OdensWalk::OdensWalk(std::string _name, double _dest[], int _uptime){

    name = _name;

    finish_flag = false;
    dest[0] = _dest[0]; // x axis(goal to goal)
    dest[1] = _dest[1]; // y axis(side by side)

    t = 0;
    uptime = _uptime;

    mw.setTsup(0.24);//歩行周期。設定は0.02[s]間隔
    mw.setdblflag(false);//両脚支持期間の有無。基本falseで
    mw.setupleg(0.05);//足をあげる高さ

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
    mypos[0] = w.getXY(0);
    mypos[1] = w.getXY(1);

    double myangle = w.getABSANGLE()*M_PI/180;
    double destangle = -atan2(dest[1]-mypos[1], dest[0]-mypos[0]);

    double distance = sqrt(pow(dest[0]-mypos[0], 2.0) +
                           pow(dest[1]-mypos[1], 2.0));

    // if (distance <= 0.5 || w.confXY() == 300 || t>uptime)
    // {
    //     act = false;
    // }
    t+=1;

    // compute rotation from abs point
    rotation = - (destangle + myangle);
    
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
        step_x = fabs(distance * cos(rotation)); // soutai zengo
        step_y = fabs(distance * sin(rotation)); // soutai sayuu
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
        finish_flag = false;
    }else{
        finish_flag = true;
    }

    setAngle(w, joint, velocity);

    return angleToString();

}


bool OdensWalk::set(jointID id, double velocity){
  const double EPS = 0.2; // just like margin of error
  double current = 0.0;

  angleMap[id] = velocity * RADTODEG;
  return true;
}

void OdensWalk::setAngle(World& w, double joint[], double velocity[]){

    double gain = 1;
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
