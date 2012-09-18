#ifndef LDRIBBLE_H
#define LDRIBBLE_H

#include "ticktackbase.h"

  class LDribble : public TicktackBase{
    public:
      LDribble();
      ~LDribble();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
