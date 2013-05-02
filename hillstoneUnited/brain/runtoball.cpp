#include "runtoball.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

RunToBall::RunToBall(World& w){
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

    elementList.push_back(new SequenceMovement("LAROUND"));
}

void RunToBall::judgement(World& w){
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
        if(w.getABSANGLE() > 180){
            temp_abs = w.getABSANGLE();
        } else {
            temp_abs = w.getABSANGLE();
        }

        if(bal[0] > 6){
            if(bal[1] > 20){
                elementList.push_back(new TicktackBase("TLEFT", t_count));
            } else if(bal[1] > -20){
                elementList.push_back(new GABase("GA_FORWARD", 200));
            } else {
                elementList.push_back(new TicktackBase("TRIGHT", t_count));
            }
        }else if(bal[0] > 3){
            if(bal[1] > 10){
                elementList.push_back(new TicktackBase("TLEFT", t_count));
            }else if(bal[1] > -10){
                elementList.push_back(new GABase("GA_FORWARD", 100));
            }else{
                elementList.push_back(new TicktackBase("TRIGHT", t_count));
            }
        }else{
            elementList.push_back(new OdensWalk(ballpos));
        }
    }
}

void RunToBall::updateFinishFlag(World& w)
{
    if (abs(ballpos[0] - x) < 0.8 &&
        abs(ballpos[1] - y) < 0.8)
    {
        finish_flag = true;
    } else {
        finish_flag = false;
    }
}


// bool RunToBall::isClose(w)
// {
//     if (abs(ballpos[0] - x) < 0.8 &&
//         abs(ballpos[1] - y) < 0.8)
//     {
//         return true;  
//     } else {
//         return false;
//     }
// }


// void RunToBall::judgement(World& w){
//     for(int i=0; i<2; i++){
//       ballpos[i] = w.getBXY(i);
//       bal[i] = w.getBAL(i);
//     }
//     conf_ballpos = w.confBXY();
//     conf_bal = w.confBAL();
//     x = w.getXY(0);
//     y = w.getXY(1);
//     conf_XY = w.confXY();

//     t_count = abs(15 * bal[1] / 360);
//     if(t_count == 0){
//       t_count = 1;
//     }

//     if (!elementList.empty())
//     {
//         if (elementList.front()->isFinished())
//         {

//             ElementBase* tmp = elementList.front();
//             delete tmp;
//             elementList.pop_front();

//             if (abs(ballpos[0] - x) < 0.8 &&
//                 abs(ballpos[1] - y) < 0.8)
//             {

//                 finish_flag = true;
//                 return elementList.front()->getNextAngle(w);
            
//             }else{

//                 if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
//                     elementList.push_back(new TicktackBase("TLEFT", 2));
//                     elementList.push_back(new SequenceMovement("LAROUND"));
//                     finish_flag = false;
//                     return elementList.front()->getNextAngle(w);
//                 } else {
//                     if(w.getABSANGLE() > 180){
//                         temp_abs = w.getABSANGLE();
//                     } else {
//                         temp_abs = w.getABSANGLE();
//                     }
//                 }

//                 if(bal[0] > 6){
//                     if(bal[1] > 20){
//                         elementList.push_back(new TicktackBase("TLEFT", t_count));
//                     } else if(bal[1] > -20){
//                         elementList.push_back(new GABase("GA_FORWARD", 200));
//                     } else {
//                         elementList.push_back(new TicktackBase("TRIGHT", t_count));
//                     }
//                 }else if(bal[0] > 3){
//                     if(bal[1] > 10){
//                         elementList.push_back(new TicktackBase("TLEFT", t_count));
//                     }else if(bal[1] > -10){
//                         elementList.push_back(new GABase("GA_FORWARD", 100));
//                     }else{
//                         elementList.push_back(new TicktackBase("TRIGHT", t_count));
//                     }
//                 }else{
//                     elementList.push_back(new OdensWalk(ballpos));
//                 }
//                 finish_flag = false;
//                 return elementList.front()->getNextAngle(w);
//             }
//         }else{

//             finish_flag = false;
//             return elementList.front()->getNextAngle(w);

//         }
//     }else{
//         if(abs(ballpos[0] - x) < 0.8 &&
//            abs(ballpos[1] - y) < 0.8)
//         {
//             finish_flag = true;
//             return elementList.front()->getNextAngle(w);
//         }else{
//             if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
//                 elementList.push_back(new TicktackBase("TLEFT", 2));
//                 elementList.push_back(new SequenceMovement("LAROUND"));
//                 finish_flag = false;
//                 return elementList.front()->getNextAngle(w);
//             }else{
//                 if(w.getABSANGLE() > 180){
//                     temp_abs = w.getABSANGLE();
//                 }else{
//                     temp_abs = w.getABSANGLE();
//                 }
//             }
//             if(bal[0] > 6){
//                 if(bal[1] > 20){
//                     elementList.push_back(new TicktackBase("TLEFT", t_count));
//                 }else if(bal[1] > -20){
//                     elementList.push_back(new GABase("GA_FORWARD", 200));
//                 }else{
//                     elementList.push_back(new TicktackBase("TRIGHT", t_count));
//                 }
//             }else if(bal[0] > 3){
//                 if(bal[1] > 10){
//                     elementList.push_back(new TicktackBase("TLEFT", t_count));
//                 }else if(bal[1] > -10){
//                     elementList.push_back(new GABase("GA_FORWARD", 100));
//                 }else{
//                     elementList.push_back(new TicktackBase("TRIGHT", t_count));
//                 }
//             }else{
//                 elementList.push_back(new OdensWalk(ballpos));
//             }
//             finish_flag = false;
//             return elementList.front()->getNextAngle(w);

//         }

//     }

// }
