#include "runtoball.hpp"

RunToBall::RunToBall(World& w){
    finish_flag = false;
    ballpos[0] = w.getBALLPOS(0);
    ballpos[1] = w.getBALLPOS(1);
    ballpos[0] = 0;
    ballpos[1] = 0;
    elementList.push_back(new OdensWalk(ballpos));
}

bool RunToBall::isFinished(World& w){
    ballpos[0] = w.getBALLPOS(0);
    ballpos[1] = w.getBALLPOS(1);

    if (!elementList.empty())
    {
        if (elementList.front()->isFinished())
        {

            ElementBase* tmp = elementList.front();
            delete tmp;
            elementList.pop_front();

            if (ballpos[0] - w.getMYPOS(0) < 0.8 &&
                ballpos[1] - w.getMYPOS(1) < 0.8)
            {

                return true;
            
            }else{

                elementList.push_back(new OdensWalk(ballpos));
                return false;

            }
        }else{

            return false;

        }
    }else{

        if(ballpos[0] - w.getMYPOS(0) < 0.8 &&
           ballpos[1] - w.getMYPOS(1) < 0.8)
        {
            return true;
        }else{

            elementList.push_back(new OdensWalk(ballpos));
            return false;

        }

    }

}