#ifndef BRAINBASE_H
#define BRAINBASE_H

#include <iostream>
#include <deque>
#include "../elementbase.hpp"

class BrainBase : public ElementBase {
  public:
    BrainBase(){};
    virtual ~BrainBase();

    bool isFinished();

    virtual std::string getNextAngle(World& w);

  protected:
    std::deque<ElementBase*> elementList;
    bool pushStand;
    std::string rtn;

    bool finishAllChild(World& w);
    void judgeStandup(World& w);

    virtual void judgement(World& w){};
    virtual void updateFinishFlag(World& w){};
};

#endif
