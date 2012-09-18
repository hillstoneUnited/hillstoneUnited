#include "dribble.h"

Dribble::Dribble(){};

Dribble::~Dribble(){};

std::string Dribble::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.586667;wX=0.013187;wY=0.666667;Threshold=1.175953;Gain=1.286168;
  //max_H = 3;
  cycle = 20.0;
  S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_rlj3 -= L;
  m_rlj5 += L;
  m_llj3 += L;
  m_llj5 -= L;
  
  /** Angle set & step count part **/
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
