#ifndef KICK_H
#define KICK_H

#include "movementbase.hpp"
#include "../util.hpp"

class Kick : public MovementBase{
  public:
    Kick();
    ~Kick();

    std::string getNextAngle(World& w);
    
  private:

    int ts;
  enum behaviorState{
    ACT,
    SETTING,
    FIRE,
  };
  behaviorState state;

};

#endif
