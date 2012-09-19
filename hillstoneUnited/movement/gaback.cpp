#include "gaback.h"

GABack::GABack(){};

GABack::~GABack(){};

std::string GABack::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** settring Parameters **/
  ga_W = 21.19;
  ga_I = 0.48;
  ga_param[1][2] = -30;//add120502

  ga_param[2][0] = 17.36;
  ga_param[2][1] = 162.81;
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
  ga_param[8][0] = 17.23;
  ga_param[8][1] = 34.06;
  ga_param[8][2] = 13.75;
  ga_param[9][0] = 30.42;
  ga_param[9][1] = 120.58;
  ga_param[9][2] = -59.26;
  ga_param[10][0] = 29.85;
  ga_param[10][1] = 267.69;
  ga_param[10][2] = 26.55;;
  ga_param[13][0] = 17.23;
  ga_param[13][1] = 34.06;
  ga_param[13][2] = 13.75;
  ga_param[14][0] = 30.42;
  ga_param[14][1] = 120.58;
  ga_param[14][2] = -59.26;
  ga_param[15][0] = 29.85;
  ga_param[15][1] = 267.69;
  ga_param[15][2] = 26.55;
  ga_Gain = 0.5;  

  /** Angle set & step count part **/
  updateAngle();
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
