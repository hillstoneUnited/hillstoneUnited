#ifndef BRAINBASE_H
#define BRAINBASE_H

#include <iostream>
#include <deque>
#include "../elementbase.h"

class BrainBase : public ElementBase {
  public:
    BrainBase();
    ~BrainBase();

    std::string getNextString(World& w);

  protected:
    std::deque<ElementBase*> elementList;
};

#endif
