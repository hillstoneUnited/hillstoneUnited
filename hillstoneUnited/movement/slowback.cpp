#include "slowback.h"

SlowBack::SlowBack(){};

SlowBack::~SlowBack(){};

std::string SlowBack::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** calculation part **/
  r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
  // cycle 20
  max_H = 2;
  cycle = 20.0;
  S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_rlj3 += L;
  m_rlj5 -= L;
  m_llj3 -= L;
  m_llj5 += L;
  
  /** Angle set & step count part **/
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
