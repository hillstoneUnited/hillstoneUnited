#ifndef BACK_H
#define BACK_H

#include "ticktackbase.h"

  class Back : public TicktackBase{
    public:
      Back();
      ~Back();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
