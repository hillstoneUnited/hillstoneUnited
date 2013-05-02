#ifndef BRAINBASE_H
#define BRAINBASE_H

#include <iostream>
#include <deque>
#include "../elementbase.hpp"

class BrainBase : public ElementBase {
  public:
    BrainBase(){};
    ~BrainBase();

    bool isFinished();

    std::string getNextAngle(World& w);

  protected:
    std::deque<ElementBase*> elementList;
    bool pushStand;
    std::string rtn;

    virtual void judgement(World& w){};
    virtual void updateFinishFlag(World& w){};
};

#endif