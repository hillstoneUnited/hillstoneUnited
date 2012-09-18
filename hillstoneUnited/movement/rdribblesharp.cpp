#include "rdribblesharp.h"

RDribbleSharp::RDribbleSharp(){};

RDribbleSharp::~RDribbleSharp(){};

std::string RDribbleSharp::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** calculation part **/
  r=0.586667;wX=0.013187;wY=0.666667;Threshold=1.175953;Gain=1.286168;
  //28,9 --> OK!
  //max_H = 3;
  cycle = 20.0;
  S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
  L = S * cos(cycle * t);
  m_llj3 += L * wY;
  m_llj5 -= L * wY;
  m_rlj3 -= L * wY * 0.1;
  m_rlj5 += L * wY * 0.1; 

  /** Angle set & step count part **/
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
