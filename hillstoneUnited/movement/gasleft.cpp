#include "gasleft.h"

GASLeft::GASLeft(){};

GASLeft::~GASLeft(){};

std::string GASLeft::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** settring Parameters **/
  ga_W = 25.18;
  ga_I = 0.53;
  ga_param[1][2] = -30;//add120502

  ga_param[2][2] = -90;
  ga_param[3][0] = 0;
  ga_param[3][1] = 0;
  ga_param[3][2] = 0;
  ga_param[4][0] = 0;
  ga_param[4][1] = 0;
  ga_param[4][2] = 90;
  ga_param[5][0] = 0;
  ga_param[5][1] = 0;
  ga_param[5][2] = 90;  
  ga_param[7][0] = 34.71;
  ga_param[7][1] = 46.4;
  ga_param[7][2] = -22.32;
  ga_param[11][0] = 24.4;
  ga_param[11][1] = 24.4;
  ga_param[11][2] = -3.24;
  ga_param[12][0] = 28.49;
  ga_param[12][1] = 327.19;
  ga_param[12][2] = -3.26;
  ga_param[16][0] = 4.56;
  ga_param[16][1] = 147.04;
  ga_param[16][2] = -0.03;
  ga_Gain = 0.5;
  
  /** Angle set & step count part **/
  updateAngle();
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
