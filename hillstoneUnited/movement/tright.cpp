#include "tright.h"

TRight::TRight(){};

TRight::~TRight(){};

std::string TRight::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** calculation part **/
  r=0.997143;wX=0.012308;wY=0.25;Threshold=0.0;Gain=0.0;// cycle 30
  H = 0;
  cycle = 30.0;
  // Right direction
  L = (1.0 - cos(cycle * t)) * wY;
  // Set angle
  m_rlj1 = -L;
  m_llj1 = -L;
  // std::cout << "TRIGHT" << std::endl;
  
  /** Angle set & step count part **/
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
