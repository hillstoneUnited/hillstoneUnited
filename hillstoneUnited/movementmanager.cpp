#include "movementmanager.h"

MovementManager::MovementManager(){
  gaMovement = new GAMovement();
  poseMovement = new PoseMovement();
  ticktackMovement = new TicktackMovement();
  kickMovement = new KickMovement;
  standupMovement = new StandupMovement();
  ffMovement = new FFMovement();
}

MovementManager::~MovementManager(){}


std::string MovementManager::nextStr(Action act, World& w){
  switch(act.name){
    case DUMMY:
      //case FLEFT:
      //case FRIGHT:
    case FFORWARD:
      return poseMovement -> getNextAngle(act, w);
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
      return ticktackMovement -> getNextAngle(act, w);
      break;
    case KICK:
      return kickMovement -> getNextAngle(act, w);
      break;
    case GA_FORWARD:
    case GA_BACK:
    case GA_L_DRIBBLE_SHARP:
    case GA_R_DRIBBLE_SHARP:
    case GA_SLEFT:
    case GA_SRIGHT:
    case GAWALKING:
      return gaMovement -> getNextAngle(act, w);
      break;
      // case LAROUND: // LAROUND defined ticktackAction
      //   editorAction(decision.action, world);
      //   decision.discount();
      //   break;
    case STANDUP:
      return standupMovement -> getNextAngle(act, w);
      break;
    default:
      std::cerr << "Walking::nextAngle : error" << std::endl;
      break;
    }
}

