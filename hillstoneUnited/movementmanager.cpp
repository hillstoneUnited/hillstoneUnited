#include "movementmanager.h"

MovementManager::MovementManager(){
  gam = new GAMovement();
  pm = new PoseMovement();
}

MovementManager::~MovementManager(){}

/*
std::string MovementManager::nextStr(Action act, &World w){
  switch(act){


    default:
      cerr
      break;
    }
}
*/
