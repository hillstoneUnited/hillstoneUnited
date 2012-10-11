#ifndef TLEFTIN_H
#define TLEFTIN_H

#include "ticktackbase.h"

  class TLeftIn : public TicktackBase{
    public:
      TLeftIn();
      ~TLeftIn();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
