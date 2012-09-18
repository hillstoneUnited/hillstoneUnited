#ifndef SRIGHT_H
#define SRIGHT_H

#include "ticktackbase.h"

  class SRight : public TicktackBase{
    public:
      SRight();
      ~SRight();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
