#ifndef LDRIBBLESHARP_H
#define LDRIBBLESHARP_H

#include "ticktackbase.h"

  class LDribbleSharp : public TicktackBase{
    public:
      LDribbleSharp();
      ~LDribbleSharp();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
