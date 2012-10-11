#ifndef FORWARD_H
#define FORWARD_H

#include "ticktackbase.h"

  class Forward : public TicktackBase{
    public:
      Forward();
      ~Forward();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
