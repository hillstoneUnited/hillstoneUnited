#include "tleft.h"

TLeft::TLeft(){};

TLeft::~TLeft(){};

std::string TLeft::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.997143;wX=0.012308;wY=0.25;Threshold=0.0;Gain=0.0;// cycle 30
  H = 0;
  cycle = 30.0;
  L = (1.0 - cos(cycle * t - M_PI)) * wY;
  // Set angle
  m_rlj1 = -L;
  m_llj1 = -L;
  // std::cout << "TLEFT" << std::endl;
  
  /** Angle set & step count part **/
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
