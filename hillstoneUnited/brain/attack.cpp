#include "attack.hpp"

Attack::Attack(World& w, double _initpos[]) {
    finish_flag = false;
    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
    judgement(w);
}

bool Attack::isFinished() {
    return finish_flag;
}

std::string Attack::getNextAngle(World& w) {
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

void Attack::judgement(World& w) {
    if (tmpflag)
    {
        elementList.push_back(new TicktackBase("TLEFT", 10));
    } else {
        elementList.push_back(new TicktackBase("FORWARD", 10));
    }
    std::cout << "judgement desu no!!" << std::endl;
    std::cout << "next: " << typeid(*elementList.front()).name() << std::endl;
}