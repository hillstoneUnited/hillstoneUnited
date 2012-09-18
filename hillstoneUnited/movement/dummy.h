#ifndef DUMMY_H
#define DUMMY_H

#include "movementbase.h"
#include "../util.h"

class Dummy : public MovementBase{
  public:
    Dummy();
    ~Dummy();

    std::string getNextAngle(Action& act, World& w);
    
  private:
};

#endif
