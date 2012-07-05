#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <iostream>
#include "world.h"
#include "util.h"
#include "movement/posemovement.h"
#include "movement/gamovement.h"

  class MovementManager{
    
    public:
      MovementManager();
      ~MovementManager();

      // std::string nextStr(Action act, &World, w);

    private:
      GAMovement* gam;
      PoseMovement* pm;
    
  };
#endif
