#ifndef RDRIBBLE_H
#define RDRIBBLE_H

#include "ticktackbase.h"

  class RDribble : public TicktackBase{
    public:
      RDribble();
      ~RDribble();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
