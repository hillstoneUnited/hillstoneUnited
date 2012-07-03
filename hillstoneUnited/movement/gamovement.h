#ifndef GAMOVEMENT_H
#define GAMOVEMENT_H

#include "movementbase.h"
#include "../util.h"

class GAMovement : public MovementBase{
  public:
    GAMovement();
    ~GAMovement();

    std::string getNextAngle(Action act, World& w);
    
  private:
};

#endif
