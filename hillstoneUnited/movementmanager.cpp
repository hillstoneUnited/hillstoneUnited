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
      std::cout << "do nothing!" << std::endl;
      return "hoge";
      break;
    case FORWARD:
      return forward.getNextAngle(act, w);
      break;
    case SLOW_FORWARD:
      return slowForward.getNextAngle(act, w);
      break;
    case DRIBBLE:
      return dribble.getNextAngle(act, w);
      break;
    case R_DRIBBLE:
      return rDribble.getNextAngle(act, w);
      break;
    case L_DRIBBLE:
      return lDribble.getNextAngle(act, w);
      break;
    case R_DRIBBLE_SHARP:
      return rDribbleSharp.getNextAngle(act, w);
      break;
    case L_DRIBBLE_SHARP:
      return lDribbleSharp.getNextAngle(act, w);
      break;
    case BACK:
      return back.getNextAngle(act, w);
      break;
    case SLOW_BACK:
      return slowBack.getNextAngle(act, w);
      break;
    case TLEFT:
      return tLeft.getNextAngle(act, w);
      break;
    case TRIGHT:
      return tRight.getNextAngle(act, w);
      break;
    case TLEFT_IN:
      return tLeftIn.getNextAngle(act, w);
      break;
    case TRIGHT_IN:
      return tRightIn.getNextAngle(act, w);
      break;
    case SLEFT:
      return sLeft.getNextAngle(act, w);
      break;
    case SRIGHT:
      return sRight.getNextAngle(act, w);
      break;
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
      std::cout << "do nothing!" << std::endl;
      return "hoge";
      break;
    case STANDUP:
      return standup.getNextAngle(act, w);
      break;
    default:
      std::cerr << "Walking::nextAngle : error" << std::endl;
      break;
    }
}

