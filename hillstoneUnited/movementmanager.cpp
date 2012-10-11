#include "movementmanager.h"

MovementManager::MovementManager(){
  ts = 0;
}

MovementManager::~MovementManager(){}

void MovementManager::stepCount(Action& act, int& ts){
  ts++;
  if(act.isFinished()){
  /*
   * for the exceptional Movement class which want to manage act.count and
   * act.finished by itself. These movements would not use act.count for
   * checking wheather action has been finished or not.
   */
    act.setCount(0);
  }else{
    act.setCount((act.getCount() - 1));
    if(act.getCount() <= 0){
      act.setCount(0);
      act.setFinished(true);
    }
  }

  std::cout << "****** ts added!!!" << std::endl;
  std::cout << "****** act.count: " << act.getCount() << std::endl;
}

std::string MovementManager::nextStr(Action& act, World& w){

  MovementBase* nowMovement;
  switch(act.getName()){
    case DUMMY: nowMovement = &dummy; break;
    case FFORWARD:
    case STOP:
      std::cout << "do nothing!" << std::endl;
      nowMovement = &dummy; break;
      break;
    case FORWARD: nowMovement = &forward; break;
    case SLOW_FORWARD: nowMovement = &slowForward; break;
    case DRIBBLE: nowMovement = &dribble; break;
    case R_DRIBBLE: nowMovement = &rDribble; break;
    case L_DRIBBLE: nowMovement = &lDribble; break;
    case R_DRIBBLE_SHARP: nowMovement = &rDribbleSharp; break;
    case L_DRIBBLE_SHARP: nowMovement = &lDribbleSharp; break;
    case BACK: nowMovement = &back; break;
    case SLOW_BACK: nowMovement = &slowBack; break;
    case TLEFT: nowMovement = &tLeft; break;
    case TRIGHT: nowMovement = &tRight; break;
    case TLEFT_IN: nowMovement = &tLeftIn; break;
    case TRIGHT_IN: nowMovement = &tRightIn; break;
    case SLEFT: nowMovement = &sLeft; break;
    case SRIGHT: nowMovement = &sRight; break;
    case LAROUND:
    case FLEFT:
    case FRIGHT:
    case KICK:
      std::cout << "do nothing!" << std::endl;
      nowMovement = &dummy;
      break;
    case GA_FORWARD: nowMovement = &gaForward; break;
    case GA_BACK: nowMovement = &gaBack; break;
    case GA_L_DRIBBLE_SHARP: nowMovement = &galDribbleSharp; break;
    case GA_R_DRIBBLE_SHARP: nowMovement = &garDribbleSharp; break;
    case GA_SLEFT: nowMovement = &gasLeft; break;
    case GA_SRIGHT: nowMovement = &gasRight; break;
    case GAWALKING:
      std::cout << "don't use GAWalking!!!!" << std::endl;
      nowMovement = &dummy;
      break;
    case FFWALK:
      std::cout << "do nothing!" << std::endl;
      nowMovement = &dummy;
      break;
    case STANDUP: nowMovement = &standup; break;
    default:
      std::cerr << "Walking::nextAngle : error" << std::endl;
      nowMovement = &dummy;
      break;
  }

  std::string returnValue = (nowMovement -> getNextAngle(act, w, ts));
  stepCount(act, ts);
  return returnValue;
}

