#ifndef SLEFT_H
#define SLEFT_H

#include "ticktackbase.h"

  class SLeft : public TicktackBase{
    public:
      SLeft();
      ~SLeft();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
