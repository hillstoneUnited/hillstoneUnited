#include "slowforward.h"

SlowForward::SlowForward(){};

SlowForward::~SlowForward(){};

std::string SlowForward::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
  // cycle 20
  max_H = 3;
  cycle = 20.0;
  S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_rlj3 -= L;
  m_rlj5 += L;
  m_llj3 += L;
  m_llj5 -= L;
  
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
