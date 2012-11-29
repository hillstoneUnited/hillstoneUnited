#ifndef STANDUP_H
#define STANDUP_H

#include "movementbase.h"
#include "../util.h"

class Standup : public MovementBase{
  public:
    Standup();
    ~Standup();

    std::string getNextAngle(World& w);
    
  private:

    static int ts;

};

#endif
