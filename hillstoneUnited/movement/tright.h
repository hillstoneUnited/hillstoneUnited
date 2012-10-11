#ifndef TRIGHT_H
#define TRIGHT_H

#include "ticktackbase.h"

  class TRight : public TicktackBase{
    public:
      TRight();
      ~TRight();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
