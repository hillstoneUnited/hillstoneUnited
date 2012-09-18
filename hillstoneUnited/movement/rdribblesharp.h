#ifndef RDRIBBLESHARP_H
#define RDRIBBLESHARP_H

#include "ticktackbase.h"

  class RDribbleSharp : public TicktackBase{
    public:
      RDribbleSharp();
      ~RDribbleSharp();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
