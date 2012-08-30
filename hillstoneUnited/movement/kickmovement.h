#ifndef KICKMOVEMENT_H
#define KICKMOVEMENT_H

#include "movementbase.h"
#include "../util.h"

class KickMovement : public MovementBase{
  public:
    KickMovement();
    ~KickMovement();

    std::string getNextAngle(Action act, World& w);
    
  private:
};

#endif
