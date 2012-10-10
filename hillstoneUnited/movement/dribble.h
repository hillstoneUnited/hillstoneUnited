#ifndef DRIBBLE_H
#define DRIBBLE_H

#include "ticktackbase.h"

  class Dribble : public TicktackBase{
    public:
      Dribble();
      ~Dribble();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
