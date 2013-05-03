#include "adjusttoball.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

AdjustToBall::AdjustToBall(World& w){
    finish_flag = false;
    
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY(0);
    y = w.getXY(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);

    judgement(w);
    updateFinishFlag(w);
}

void AdjustToBall::judgement(World& w){
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY(0);
    y = w.getXY(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);
    if(t_count == 0){
      t_count = 1;
    }

    if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
        elementList.push_back(new TicktackBase("TLEFT", 2));
        elementList.push_back(new SequenceMovement("LAROUND"));
    } else {

        if(bal[1] > 10){
            elementList.push_back(new TicktackBase("TLEFT", t_count));
        }else if(bal[1] > -10){
            elementList.push_back(new SequenceMovement("DUMMY"));
            elementList.push_back(new TicktackBase("SLOW_FORWARD", 3));
            elementList.push_back(new TicktackBase("DRIBBLE", 4));
            elementList.push_back(new SequenceMovement("LAROUND"));
        }else{
            elementList.push_back(new TicktackBase("TRIGHT", t_count));
        }
    }

    std::cout << w.getBAL(0) << std::endl;
    std::cout << "adjusting" << std::endl;
}

void AdjustToBall::updateFinishFlag(World& w)
{
    if (w.getBAL(0) < 0.8 &&
        w.confBAL() <= 150 &&
        !w.isFalling())
    {
        finish_flag = true;
    } else {
        finish_flag = false;
    }
}
