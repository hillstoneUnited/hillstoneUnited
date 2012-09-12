#include "ffwalk.h"

FFWalk::FFWalk(){
  for(int i=0; i<6; i++){
    for(int j=0; j<3; j++){
      joints[i].angle[j] = 0;
      joints[i].axis[j] = 0;
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


std::string FFWalk::getNextAngle(Action act, World& w){
  return angleToString();
}

void FFWalk::inverseKinematics(){
  // to calculate P5
  double p5[] = {0,0,0};
  p5[0] = target.point[0] - l6 * target.yuganA[0];
  p5[1] = target.point[1] - l6 * target.yuganA[1];
  p5[2] = target.point[2] - l6 * target.yuganA[2];

  // to calculate theta1
  double theta1 = atan2(target.yuganB[1], target.yuganB[0]);
  
  // to calculate theta3, 4
  
  // to calculate theta5
  
  // to calculate theta6, 2
  
  // to set the angle with set()
}
