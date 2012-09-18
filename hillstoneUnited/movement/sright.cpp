#include "sright.h"

SRight::SRight(){};

SRight::~SRight(){};

std::string SRight::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.997143;wX=0.012308;wY=0.2;Threshold=0.0;Gain=0.0;// cycle 30
  H = 0;
  cycle = 30.0;
  L = (1.0 - cos(cycle * t)) * wY;
  m_llj2 += L;
  m_llj6 -= L;
  m_rlj2 -= L;
  m_rlj6 += L;  

  /** Angle set & step count part **/
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
