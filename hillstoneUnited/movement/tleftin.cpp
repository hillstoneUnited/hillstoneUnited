#include "tleftin.h"

TLeftIn::TLeftIn(){};

TLeftIn::~TLeftIn(){};

std::string TLeftIn::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** calculation part **/
  r=0.727619;wX=0.034286;wY=0.075;Threshold=0.0;Gain=0.35;// cycle 30
  H = 0;
  cycle = 30.0;
  L = (1.0 - cos(cycle * t - M_PI)) * wY;
  m_rlj2 -= L;
  m_rlj6 += L;
  m_llj2 += L;
  m_llj6 -= L;
  L = Gain * cos(cycle * t - M_PI);
  m_rlj3 -= L;
  m_rlj5 += L;
  m_llj3 -= L;
  m_llj5 += L;
  
  /** Angle set & step count part **/
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
