#include "brainbase.hpp"
#include "../movement/standup.hpp"

BrainBase::~BrainBase(){
  while (!elementList.empty()) {
    ElementBase* tmp = elementList.front();
    delete tmp;
    elementList.pop_front();
  }
}

bool BrainBase::isFinished(){
  return finish_flag;
}

std::string BrainBase::getNextAngle(World& w) {
    // if (w.isFalling())
    // {
    //     if (!pushStand)
    //     {
    //         elementList.clear();
    //         elementList.push_front(new Standup());
    //         pushStand = true;
    //     } else {
    //         if (elementList.front()->isFinished())
    //         {
    //             ElementBase* tmp = elementList.front();
    //             delete tmp;
    //             elementList.pop_front();
    //             elementList.push_front(new Standup());
    //             pushStand = true;
    //         } else {

    //         }
    //     }
    //     rtn = elementList.front()->getNextAngle(w);
    //     if (elementList.empty())
    //     {
    //         updateFinishFlag(w);
    //     }
    //     return rtn;
    // }

    pushStand = false;

    rtn = elementList.front()->getNextAngle(w);
    if (elementList.front()->isFinished())
    {
        ElementBase* tmp = elementList.front();
        delete tmp;
        elementList.pop_front();
    }
    if (finishAllChild(w))
    {
        updateFinishFlag(w);
    }
    return rtn;
    // if (!elementList.empty())
    // {
    //     if (!elementList.front()->isFinished())
    //     {
    //         return elementList.front()->getNextAngle(w);
    //     } else {
    //         ElementBase* tmp = elementList.front();
    //         delete tmp;
    //         elementList.pop_front();

    //         if (!elementList.empty())
    //         {
    //         } else {
    //             judgement(w);
    //         }
    //         rtn = elementList.front()->getNextAngle(w);
    //         if(elementList.empty()){
    //         	updateFinishFlag(w);
    //         }
    //         return rtn;
    //     }
    // } else {
    //     judgement(w);
    //     rtn = elementList.front()->getNextAngle(w);
    //     if (elementList.empty())
    //     {
    //         updateFinishFlag(w);
    //     }
    //     return rtn;
    // }
}

bool BrainBase::finishAllChild(World& w) {
    if (elementList.empty())
    {
        return true;
    } else {
        for (int i = 0; i < (int)elementList.size(); i++)
        {
            if (!(elementList[i]->isFinished()))
            {
                return false;
            }
        }
        return true;
    }
}

void BrainBase::judgeStandup(World& w) {
    if (w.isFalling())
    {
        elementList.push_front(new Standup());
    }
}
