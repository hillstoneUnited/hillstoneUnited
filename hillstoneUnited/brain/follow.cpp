#include "follow.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

Follow::Follow(World& w, double _offx, double _offy){
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

    offx = _offx;
    offy = _offy;

    offdist = sqrt(pow(offx, 2.0)+pow(offy, 2.0));
    offangle = atan2(offy, offx) * 180/M_PI;

    t_count = abs(15 * bal[1] / 360);

    judgement(w);
    updateFinishFlag(w);
}

void Follow::judgement(World& w){
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY_AVE(i);
      bal[i] = w.getBAL(i);
    }

    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY_AVE(0);
    y = w.getXY_AVE(1);
    conf_XY = w.confXY();

    double targetx = ballpos[0]+offx;
    double targety = ballpos[1]+offy;

    bal[1] = atan2(targety-y, targetx-x) * 180/M_PI;

    t_count = abs(15 * bal[1] / 360);
    if(t_count == 0){
      t_count = 1;
    }

    if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
        elementList.push_back(new TicktackBase("TLEFT", 2));
        elementList.push_back(new SequenceMovement("LAROUND"));
    } else {

        if (false)
        {
            if (bal[1] >= 20)
            {
                elementList.push_back(new TicktackBase("TLEFT", 2));
            } else if (bal[1] <= -20) {
                elementList.push_back(new TicktackBase("TRIGHT", 2));
            } else {
                elementList.push_back(new TicktackBase("FORWARD", 3));
                elementList.push_back(new GABase("GA_FORWARD", bal[0]*15));
            }
        } else {

            if (bal[1] >= 20)
            {
                elementList.push_back(new TicktackBase("TLEFT", 2));
            } else if (bal[1] <= -20) {
                elementList.push_back(new TicktackBase("TRIGHT", 2));
            } else {

                elementList.push_back(new OdensWalk("BALL", offx, offy));
            }
        }


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

void Follow::updateFinishFlag(World& w)
{ // 0.73
    // std::cout << "##adjust update##\tbal[0]: " << w.getBAL(0) <<
    // "\tconfBAL: " << w.confBAL() <<
    // "\tabs(w.getBAL): " << abs(w.getBAL(1)) << std::endl;
    if (ballpos[0]+offx < 0.5 &&
        ballpos[1]+offy < 0.5 &&
        w.confBAL() <= 200 &&
        abs(w.getBAL(1)) <= 80 &&
        !w.isFalling())
    {
        finish_flag = true;
    } else {
        finish_flag = false;
        judgement(w);
    }
}
