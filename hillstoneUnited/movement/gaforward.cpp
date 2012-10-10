#include "gaforward.h"

GAForward::GAForward(){};

GAForward::~GAForward(){};

std::string GAForward::getNextAngle(Action& act, World& w, int& ts){
  /** Init **/
  resetAngleMap();
  renew(ts);

  /** settring Parameters **/
  ga_W = 28.02;
  ga_I = 1.67;
  ga_param[1][2] = -30;//add120502

  ga_param[2][0] = 4.44;
  ga_param[2][1] = 260.48;
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
  ga_param[8][0] = 38.41;
  ga_param[8][1] = 102.44;
  ga_param[8][2] = 13.25;
  ga_param[9][0] = 41.36;
  ga_param[9][1] = 17.85;
  ga_param[9][2] = -70.55;
  ga_param[10][0] = 10.23;
  ga_param[10][1] = 134.37;
  ga_param[10][2] = 55.31;
  ga_param[13][0] = 38.41;
  ga_param[13][1] = 102.44;
  ga_param[13][2] = 13.25;
  ga_param[14][0] = 41.36;
  ga_param[14][1] = 17.85;
  ga_param[14][2] = -70.55;
  ga_param[15][0] = 10.23;
  ga_param[15][1] = 134.37;
  ga_param[15][2] = 55.31;
  ga_Gain = 0.5; 
  
  /** Angle set & step count part **/
  updateAngle();
  setAngle(w);
  // stepCount(act);
  return angleToString();
}
