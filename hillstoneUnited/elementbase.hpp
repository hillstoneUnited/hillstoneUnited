#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <iostream>
#include "world.hpp"

class ElementBase {
  public:
    ElementBase(){};
    ~ElementBase(){};

    virtual bool isFinished(){};

    virtual std::string getNextAngle(World& w){};

  protected:
    bool finish_flag;
};

#endif
