#ifndef TRIGHTIN_H
#define TRIGHTIN_H

#include "ticktackbase.h"

  class TRightIn : public TicktackBase{
    public:
      TRightIn();
      ~TRightIn();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
