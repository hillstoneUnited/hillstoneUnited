#include "forward.h"

Forward::Forward(){};

Forward::~Forward(){};

std::string Forward::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.905714;wX=0.314335;wY=1.819048;Threshold=2.381232;Gain=1.383409;
    // cycle 20 -> upright
  cycle = 20.0;
  S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_rlj3 -= L;
  m_rlj5 += L;
  m_llj3 += L;
  m_llj5 -= L;
  // std::cout << "FORWARD" << std::endl;
  
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
