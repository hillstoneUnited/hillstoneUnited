#ifndef STANDUPMOVEMENT_H
#define STANDUPMOVEMENT_H

#include "movementbase.h"
#include "../util.h"

class StandupMovement : public MovementBase{
  public:
    StandupMovement();
    ~StandupMovement();

    std::string getNextAngle(Action act, World& w);
    
  private:
};

#endif
