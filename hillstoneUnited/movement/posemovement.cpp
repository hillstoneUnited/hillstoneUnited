#include "posemovement.h"

PoseMovement::PoseMovement(){
  
}

PoseMovement::~PoseMovement(){}


std::string PoseMovement::getNextAngle(Action act, World& w){
  
  switch(act.name){
    case DUMMY:

      set(w, raj1, -100.0);
      set(w, laj1, -100.0);
      set(w, raj2, 0.0);
      set(w, laj2, 0.0);
      set(w, raj3, 90.0);
      set(w, laj3, -90.0);
      set(w, raj4, 90.0);
      set(w, laj4, -90.0);
      set(w, rlj1, 0.0, 0.01);
      set(w, llj1, 0.0, 0.01);
      set(w, rlj2, 0.0, 0.05);
      set(w, llj2, 0.0, 0.05);
      set(w, rlj3, 0.0, 0.02);
      set(w, llj3, 0.0, 0.02);
      set(w, rlj4, 0.0, 0.02);
      set(w, llj4, 0.0, 0.02);
      set(w, rlj5, 0.0, 0.02);
      set(w, llj5, 0.0, 0.02);
      set(w, rlj6, 0.0, 0.05);
      set(w, llj6, 0.0, 0.05);

      break;

    case FFORWARD:

      // TODO write the set() function in it.

      break;

    case STOP:
    case FORWARD:
    case SLOW_FORWARD:
    case DRIBBLE:
    case R_DRIBBLE:
    case L_DRIBBLE:
    case R_DRIBBLE_SHARP:
    case L_DRIBBLE_SHARP:
    case BACK:
    case SLOW_BACK:
    case TLEFT:
    case TRIGHT:
    case TLEFT_IN:
    case TRIGHT_IN:
    case SLEFT:
    case SRIGHT:
    case LAROUND:
      //in ver2. ordinally FLEFT&FRIGHT are in poseAction
    case FLEFT:
    case FRIGHT:
    case KICK:
    case GA_FORWARD:
    case GA_BACK:
    case GA_L_DRIBBLE_SHARP:
    case GA_R_DRIBBLE_SHARP:
    case GA_SLEFT:
    case GA_SRIGHT:
    case GAWALKING:
    case STANDUP:
    default:
      std::cerr << "PoseMovement::getNextAngle : error" << std::endl;
      break;
  }

  return angleToString();
}
