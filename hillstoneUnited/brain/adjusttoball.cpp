#include "adjusttoball.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

AdjustToBall::AdjustToBall(World& w){
    finish_flag = false;
    
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY_AVE(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY_AVE(0);
    y = w.getXY_AVE(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);

    judgement(w);
    updateFinishFlag(w);
}

void AdjustToBall::judgement(World& w){
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY_AVE(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY_AVE(0);
    y = w.getXY_AVE(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);
    if(t_count == 0){
      t_count = 1;
    }

    if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
        elementList.push_back(new TicktackBase("TLEFT", 2));
        elementList.push_back(new SequenceMovement("LAROUND"));
    } else {

        elementList.push_back(new SequenceMovement("LAROUND"));
        elementList.push_back(new OdensWalk("BALL", 0.5, 0));
        elementList.push_back(new SequenceMovement("DUMMY"));


        // if(bal[1] > 10){
        //     elementList.push_back(new TicktackBase("TLEFT", t_count));
        // }else if(bal[1] > -10){
        //     elementList.push_back(new SequenceMovement("READY"));
        //     elementList.push_back(new TicktackBase("FORWARD", 5));
        //     elementList.push_back(new SequenceMovement("READY"));
        //     elementList.push_back(new SequenceMovement("LAROUND"));
        // }else{
        //     elementList.push_back(new TicktackBase("TRIGHT", t_count));
        // }
    }

    // std::cout << w.getBAL(0) << std::endl;
    // std::cout << "adjusting\tnextangle" << std::endl;

    judgeStandup(w);
}

void AdjustToBall::updateFinishFlag(World& w)
{ // 0.73
    // std::cout << "##adjust update##\tbal[0]: " << w.getBAL(0) <<
    // "\tconfBAL: " << w.confBAL() <<
    // "\tabs(w.getBAL): " << abs(w.getBAL(1)) << std::endl;
    if (w.getBAL(0) < 0.9 &&
        w.confBAL() <= 150 &&
        abs(w.getBAL(1)) <= 10 &&
        !w.isFalling())
    {
        finish_flag = true;
    } else {
        finish_flag = false;
        judgement(w);
    }
}
