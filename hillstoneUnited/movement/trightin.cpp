#include "trightin.h"

TRightIn::TRightIn(){};

TRightIn::~TRightIn(){};

std::string TRightIn::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.727619;wX=0.034286;wY=0.075;Threshold=0.0;Gain=0.35;// cycle 30
  H = 0;
  cycle = 30.0;
  L = (1.0 - cos(cycle * t)) * wY;
  m_llj2 += L;
  m_llj6 -= L;
  m_rlj2 -= L;
  m_rlj6 += L;
  L = Gain * cos(cycle * t);
  m_rlj3 -= L;
  m_rlj5 += L;
  m_llj3 -= L;
  m_llj5 += L;

  /** Angle set & step count part **/
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
