#include "galdribblesharp.h"

GALDribbleSharp::GALDribbleSharp(){};

GALDribbleSharp::~GALDribbleSharp(){};

std::string GALDribbleSharp::getNextAngle(Action& act, World& w){
  /** Init **/
  resetAngleMap();
  renew(act);

  /** settring Parameters **/
  ga_W = 23.91;
  ga_I = 0.64;
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
  ga_param[8][0] = 38.24;
  ga_param[8][1] = 91.79;
  ga_param[8][2] = 17.88;
  ga_param[9][0] = 34.94;
  ga_param[9][1] = 324.25;
  ga_param[9][2] = -59.58;
  ga_param[10][0] = 11.07;
  ga_param[10][1] = 112.75;
  ga_param[10][2] = 47.67;
  ga_param[13][0] = 29.31;
  ga_param[13][1] = 91.79;
  ga_param[13][2] = 9.39;
  ga_param[14][0] = 34.66;
  ga_param[14][1] = 324.25;
  ga_param[14][2] = -52.22;
  ga_param[15][0] = 14.47;
  ga_param[15][1] = 112.75;
  ga_param[15][2] = 50.26;
  ga_Gain = 0.5;  

  /** Angle set & step count part **/
  updateAngle();
  setAngle(act, w);
  stepCount(act);
  return angleToString();
}
