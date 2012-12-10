#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <iostream>

class ElementBase {
  public:
    ElementBase();
    ~ElementBase(){};

    bool isfinished();

    virtual std::string getNextString(World& w);

  protected:
    bool finish_flag;
};

#endif
