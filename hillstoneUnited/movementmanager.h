#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <iostream>
#include "world.h"
#include "util.h"
#include "movement/posemovement.h"
#include "movement/gamovement.h"
#include "movement/ticktackmovement.h"
#include "movement/kickmovement.h"
#include "movement/standupmovement.h"
#include "movement/ffmovement.h"

  class MovementManager{
    
    public:
      MovementManager();
      ~MovementManager();

      std::string nextStr(Action& act, World& w);

    private:
      GAMovement* gaMovement;
      PoseMovement* poseMovement;
      TicktackMovement* ticktackMovement;
      KickMovement* kickMovement;
      StandupMovement* standupMovement;
      FFMovement* ffMovement;
  };
#endif
