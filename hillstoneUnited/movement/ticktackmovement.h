#ifndef TICKTACKMOVEMENT_H
#define TICKTACKMOVEMENT_H

#include "movementbase.h"
#include "../util.h"

class TicktackMovement : public MovementBase{
  public:
    TicktackMovement();
    ~TicktackMovement();

    std::string getNextAngle(Action act, World& w);
    
  private:
};

#endif
