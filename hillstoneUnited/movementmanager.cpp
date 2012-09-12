#include "movementmanager.h"

MovementManager::MovementManager(){
}

MovementManager::~MovementManager(){}


std::string MovementManager::nextStr(Action& act, World& w){
  switch(act.getName()){
    case DUMMY:
      return dummy.getNextAngle(act, w);
      break;
    case FFORWARD:
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
    case FFWALK:
      return ffWalk.getNextAngle(act, w);
      break;
    case STANDUP:
      return standup.getNextAngle(act, w);
      break;
    default:
      std::cerr << "Walking::nextAngle : error" << std::endl;
      break;
    }
}

