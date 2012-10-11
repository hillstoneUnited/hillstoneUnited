#include "rdribble.h"

RDribble::RDribble(){};

RDribble::~RDribble(){};

std::string RDribble::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** calculation part **/
  r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
  // cycle 20
  //max_H = 3;
  cycle = 20.0;
  S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_llj3 += L * wY;
  m_llj5 -= L * wY;
  m_rlj3 -= L * wY * 0.1;
  m_rlj5 += L * wY * 0.1;
 
  /** Angle set & step count part **/
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
