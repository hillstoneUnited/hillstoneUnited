#ifndef STANDUP_H
#define STANDUP_H

#include "movementbase.h"
#include "../util.h"

class Standup : public MovementBase{
  public:
    Standup();
    ~Standup();

    std::string getNextAngle(Action& act, World& w, int& ts);
    
  private:

    int ts;

};

#endif
