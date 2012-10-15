#include "ffwalk.h"

FFWalk::FFWalk(){
  for(int i=0; i<6; i++){
    joints[i].angle = 0.0;
    for(int j=0; j<3; j++){
      joints[i].axis[j] = 0.0;
    }
  }
  
  l3 = 0;
  l4 = 0;
  l6 = 0;

  for(int i=0; i<3; i++){
    yuganA[i] = 0;
    yuganB[i] = 0;

    target.point[i] = 0;
    target.yuganA[i] = 0;
    target.yuganB[i] = 0;
  }
}

FFWalk::~FFWalk(){}


std::string FFWalk::getNextAngle(Action& act, World& w, int& ts){
  
  resetAngleMap();

  return angleToString();
}

void FFWalk::inverseKinematics(){
  // to calculate P5
  double p5[] = {0,0,0};
  p5[0] = target.point[0] - l6 * target.yuganA[0];
  p5[1] = target.point[1] - l6 * target.yuganA[1];
  p5[2] = target.point[2] - l6 * target.yuganA[2];

  // to calculate joints[0].angle (theta1)
  joints[0].angle = atan2(target.yuganB[1], target.yuganB[0]);
  
  // to calculate joints[2].angle(theta3), joints[3].angle(theta4)
  double distP1P5 = sqrt(pow(p5[0],2.0) + pow(p5[1],2.0) + pow(p5[2],2.0));
  
  double c_alpha = (pow(l3,2.0) + pow(distP1P5,2.0) - pow(l4,2.0)) /
    2 * l3 * distP1P5;
  double c_beta = (pow(l3,2.0) - pow(distP1P5,2.0) + pow(l4,2.0)) /
    2 * l3 * l4;

  double theta3_dash = M_PI_2 -
    atan2(sqrt(pow(p5[0],2.0)+pow(p5[1],2.0)), p5[2]) -
    atan2(sqrt(1 - pow(c_alpha,2.0)), c_alpha);

  joints[2].angle = theta3_dash / (1+sqrt(2));
  joints[3].angle = M_PI - atan2(sqrt(1 - pow(c_beta,2.0)), c_beta);

  // to calculate joints[4].angle(theta5)
  double phi = atan2(pow(p5[0],2.0), sqrt(p5[2] + pow(p5[1],2.0)));
  double alpha = -1 * atan2(sqrt(1 - pow(c_alpha,2.0)), c_alpha);

  joints[4].angle = atan2(sqrt(pow((target.point[0]-p5[0]),2.0) +
    pow((target.point[1]-p5[1]),2.0)), (target.point[2]-p5[2])) +
    joints[3].angle - phi - alpha;
  
  // to calculate joints[5].angle(theta6), joints[1].angle(theta2)

  
  // to set the angle with set()
}
