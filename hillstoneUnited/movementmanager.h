#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <iostream>
#include "world.h"
#include "util.h"
#include "movement/forward.h"
#include "movement/slowforward.h"
#include "movement/dribble.h"
#include "movement/ldribble.h"
#include "movement/rdribble.h"
#include "movement/ldribblesharp.h"
#include "movement/rdribblesharp.h"
#include "movement/back.h"
#include "movement/slowback.h"
#include "movement/tleft.h"
#include "movement/tright.h"
#include "movement/tleftin.h"
#include "movement/trightin.h"
#include "movement/sleft.h"
#include "movement/sright.h"
#include "movement/dummy.h"
#include "movement/standup.h"
#include "movement/ffwalk.h"

  class MovementManager{
    
    public:
      MovementManager();
      ~MovementManager();

      std::string nextStr(Action& act, World& w);

    private:
      Forward forward;
      SlowForward slowForward;
      Dribble dribble;
      LDribble lDribble;
      RDribble rDribble;
      LDribbleSharp lDribbleSharp;
      RDribbleSharp rDribbleSharp;
      Back back;
      SlowBack slowBack;
      TLeft tLeft;
      TRight tRight;
      TLeftIn tLeftIn;
      TRightIn tRightIn;
      SLeft sLeft;
      SRight sRight;
      Dummy dummy;
      Standup standup;
      FFWalk ffWalk;
  };
#endif
