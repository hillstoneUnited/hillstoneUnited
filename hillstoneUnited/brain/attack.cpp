#include "attack.hpp"

Attack::Attack(World& w, double _initpos[]) {
    finish_flag = false;
    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
    judgement(w);
    tmpflag = false;
}

void Attack::judgement(World& w) {
    testJudge(w);
}

void Attack::testJudge(World& w) {
    // if (tmpflag)
    // {
    //     elementList.push_back(new TicktackBase("TLEFT", 10));
    //     tmpflag = false;
    // } else {
    //     elementList.push_back(new TicktackBase("FORWARD", 10));
    //     tmpflag = true;
    // }

    if (!tmpflag)
    {
        elementList.push_back(new RunToBall(w));
        if (elementList.front()->isFinished())
        {
            tmpflag = true;
        }
    } else {
        std::cout << "finish!!" << std::endl;
        elementList.push_back(new SequenceMovement("DUMMY"));
    }

    // elementList.push_back(new TicktackBase("SLEFT", 10)); // migi ni mawarikomi

    std::cout << "judgement desu no!!" << std::endl;
    std::cout << "next: " << typeid(*elementList.front()).name() << std::endl;
}

void Attack::updateFinishFlag(World& w) {
    finish_flag = false;
}