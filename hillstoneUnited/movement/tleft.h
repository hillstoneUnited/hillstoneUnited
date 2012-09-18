#ifndef TLEFT_H
#define TLEFT_H

#include "ticktackbase.h"

  class TLeft : public TicktackBase{
    public:
      TLeft();
      ~TLeft();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
