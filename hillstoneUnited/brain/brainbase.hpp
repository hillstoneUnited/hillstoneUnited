#ifndef BRAINBASE_H
#define BRAINBASE_H

#include <iostream>
#include <deque>
#include "../elementbase.hpp"

class BrainBase : public ElementBase {
  public:
    BrainBase();
    ~BrainBase();

    virtual bool isFinished(){};
    bool checkFinished();

    std::string getNextAngle(World& w);

  protected:
    std::deque<ElementBase*> elementList;
};

#endif
