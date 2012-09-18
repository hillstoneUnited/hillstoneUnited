#ifndef SLOWBACK_H
#define SLOWBACK_H

#include "ticktackbase.h"

  class SlowBack : public TicktackBase{
    public:
      SlowBack();
      ~SlowBack();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
