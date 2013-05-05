#include "odenswalk.hpp"

// x: distance to ball (zengo soutai)
// y: distance to ball (sayu soutai)

OdensWalk::OdensWalk(double _dest[]) {

    name = "FIXED";

    finish_flag = false;
    dest[0] = _dest[0]; // x axis(goal to goal)
    dest[1] = _dest[1]; // y axis(side by side)

    offset[0] = 0.0;
    offset[1] = 0.0;

    enemEnum = -1;

    distance = 0.0;
    rotation = 0.0;

    conf = 0;

    mw.setTsup(0.24);//歩行周期。設定は0.02[s]間隔
    mw.setdblflag(false);//両脚支持期間の有無。基本falseで
    mw.setupleg(0.05);//足をあげる高さ

}

OdensWalk::OdensWalk(std::string _name, double _offsetx, double _offsety){

    name = _name;

    finish_flag = false;

    dest[0] = 0.0;
    dest[1] = 0.0;

    offset[0] = _offsetx;
    offset[1] = _offsety;

    enemEnum = -1;

    distance = 0.0;
    rotation = 0.0;

    conf = 300;

    mw.setTsup(0.24);//歩行周期。設定は0.02[s]間隔
    mw.setdblflag(false);//両脚支持期間の有無。基本falseで
    mw.setupleg(0.05);//足をあげる高さ

}

OdensWalk::OdensWalk(int _enemEnum, double _offsetx, double _offsety){

    name = "ENEMY";

    finish_flag = false;

    dest[0] = 0.0;
    dest[1] = 0.0;

    offset[0] = _offsetx;
    offset[1] = _offsety;

    enemEnum = _enemEnum;

    distance = 0.0;
    rotation = 0.0;

    conf = 300;

    mw.setTsup(0.24);//歩行周期。設定は0.02[s]間隔
    mw.setdblflag(false);//両脚支持期間の有無。基本falseで
    mw.setupleg(0.05);//足をあげる高さ

}

OdensWalk::~OdensWalk(){}

std::string OdensWalk::getNextAngle(World& w){
    resetAngleMap();

    paramChangeByName(w);

    //MakeWalkの戻り値を受け取る
    bool isWalking;
    //前方方向の歩幅
    double step_x = 0;
    //左右方向の歩幅(左が正)
    double step_y = 0;

    //歩行信号
    //trueの場合のみ歩行する
    //falseになると、両足が着いたタイミングで停止する
    bool act = wannaWalk(w);
    
    //ボールの情報から、歩幅を決定する
    const double MAX_STEP_X = 0.09;//前後の最大歩幅
    const double MAX_STEP_Y = 0.03;//左右の最大歩幅
    const double MAX_STEP_R = 30*M_PI/180;//旋回の最大角度
    
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
    if(isWalking || !w.isFalling()){
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

void OdensWalk::paramChangeByName(World& w) {

    double myangle = w.getABSANGLE()*DEGTORAD;
    double offsetdist = sqrt(pow(offset[0], 2.0) + pow(offset[1], 2.0));
    double offsetangle = atan2(offset[1],offset[0]);

    if (name == "BALL" || name == "FIXED")
    {
        if (name == "BALL")
        {
            dest[0] = w.getBXY(0) + offset[0];
            dest[1] = w.getBXY(1) + offset[1];
            conf = w.confBXY();
        } else {
            conf++;
        }

        double mypos[2] = {};
        mypos[0] = w.getXY(0);
        mypos[1] = w.getXY(1);

        double destangle = atan2(dest[1]-mypos[1], dest[0]-mypos[0]);

        distance = sqrt(pow(dest[0]-mypos[0], 2.0) +
                        pow(dest[1]-mypos[1], 2.0));
        rotation = destangle - myangle;

    } else if (name == "GOAL") {

        rotation = ((w.getEGR(1)+w.getEGL(1))/2 + w.getABSANGLE()) * DEGTORAD;
        distance = (w.getEGR(0)+w.getEGL(0))/2;
        conf = (w.confEGR() + w.confEGL()) / 2;

    } else if (name == "ENEMY") {

        rotation = (w.getENEMY(enemEnum, 1) + w.getABSANGLE()) * DEGTORAD;
        distance = w.getENEMY(enemEnum, 0);
        conf = w.confENEMY(enemEnum);
        
    } else {
        std::cout << "BAD argument in OdensWalk. name:" <<
        name << "can't understand." << std::endl;
    }

    // double theta = rotation + myangle;
    // double phi = offset[1];
    // double ita = 180 * DEGTORAD - phi + theta;
    // double tmpdistance = sqrt(pow(distance * cos(theta) + offset[0] * cos(phi), 2.0) + pow(distance * sin(theta) + offset[0] * sin(phi), 2.0));

    // // calculate rotation by yogen teiri
    // double alpha = sqrt(pow(distance, 2.0)+pow(offset[0], 2.0) - 2 * distance * offset[0] * cos(rotation+myangle + (180*DEGTORAD - offset[1])));
    // double cosx = (pow(distance, 2.0), + pow(alpha, 2.0) - pow(offset[0], 2.0)) / (2 * distance * alpha);
    // distance = tmpdistance;
    // rotation = acos(cosx) + rotation - myangle;
}

bool OdensWalk::wannaWalk(World& w) {
    if (conf >= 250 || distance <= 0.5 || w.confXY() >= 250 || w.isFalling())
    {
        return false;
    } else {
        return true;
    }
}
