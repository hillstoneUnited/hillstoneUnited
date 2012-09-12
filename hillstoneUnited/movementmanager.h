#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <iostream>
#include "world.h"
#include "util.h"
#include "movement/dummy.h"
#include "movement/standup.h"
#include "movement/ffwalk.h"

  class MovementManager{
    
    public:
      MovementManager();
      ~MovementManager();

      std::string nextStr(Action& act, World& w);

    private:
      Dummy dummy;
      Standup standup;
      FFWalk ffWalk;
  };
#endif
