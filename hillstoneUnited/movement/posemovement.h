#ifndef POSEMOVEMENT_H
#define POSEMOVEMENT_H

#include "movementbase.h"
#include "../util.h"

class PoseMovement : public MovementBase{
  public:
    PoseMovement();
    ~PoseMovement();

    std::string getNextAngle(Action act, World& w);
    
  private:
};

#endif
