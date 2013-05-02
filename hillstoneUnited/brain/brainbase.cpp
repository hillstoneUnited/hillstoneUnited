#include "brainbase.hpp"
#include "../movement/standup.hpp"

BrainBase::~BrainBase(){
  while (!elementList.empty()) {
    ElementBase* tmp = elementList.front();
    delete tmp;
    elementList.pop_front();
  }
  pushStand = false;
}

bool BrainBase::isFinished(){
  return finish_flag;
}

std::string BrainBase::getNextAngle(World& w) {
    if (w.isFalling())
    {
        if (!pushStand)
        {
            elementList.push_front(new Standup());
            pushStand = true;
        } else {
            if (elementList.front()->isFinished())
            {
                ElementBase* tmp = elementList.front();
                delete tmp;
                elementList.pop_front();
                elementList.push_front(new Standup());
                pushStand = true;
            } else {

            }
        }
        return elementList.front()->getNextAngle(w);
    }

    pushStand = false;

    if (!elementList.empty())
    {
        if (!elementList.front()->isFinished())
        {
            return elementList.front()->getNextAngle(w);
        } else {
            ElementBase* tmp = elementList.front();
            delete tmp;
            elementList.pop_front();

            if (!elementList.empty())
            {
                return elementList.front()->getNextAngle(w);
            } else {
                judgement(w);
                return elementList.front()->getNextAngle(w);
            }
        }
    } else {
        judgement(w);
        return elementList.front()->getNextAngle(w);
    }
}
