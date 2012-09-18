#ifndef SLOWFORWARD_H
#define SLOWFORWARD_H

#include "ticktackbase.h"

  class SlowForward : public TicktackBase{
    public:
      SlowForward();
      ~SlowForward();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
