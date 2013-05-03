#include "attack.hpp"

Attack::Attack(World& w, double _initpos[]) {
    finish_flag = false;

    ballpos[0] = 0.0;
    ballpos[1] = 0.0;
    bal[0] = w.getBAL(0);
    bal[1] = w.getBAL(1);
    bal[2] = w.getBAL(2);
    mypos[0] = 0.0;
    mypos[1] = 0.0;
    balposconf = w.confBAL();
    myposconf = w.confXY();
    angle = w.getABSANGLE();
    for (int i = 0; i < 3; i++)
    {
        egr[i] = w.getEGR(i);
        egl[i] = w.getEGL(i);
    }

    field_x = w.getFieldLengthX();
    field_y = w.getFieldLengthY();

    kickAngle = 0.0;

    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
    initpos[2] = _initpos[2];
    judgement(w);
    tmpflag = false;
}

void Attack::judgement(World& w) {

    ballpos[0] = w.getBXY(0);
    ballpos[1] = w.getBXY(1);
    bal[0] = w.getBAL(0);
    bal[1] = w.getBAL(1);
    bal[2] = w.getBAL(2);
    mypos[0] = w.getXY(0);
    mypos[1] = w.getXY(1);
    balposconf = w.confBAL();
    myposconf = w.confXY();
    angle = w.getABSANGLE();
    for (int i = 0; i < 3; i++)
    {
        egr[i] = w.getEGR(i);
        egl[i] = w.getEGL(i);
    }

    kickAngle = 0.0;

    std::cout << egr[0] << std::endl;
    std::cout << egr[1] << std::endl;


    if (hasBal())
    {
        if (close2Goal())
        {
            // shoot
            std::cout << "shoot!!" <<std::endl;
            kickAngle = (egr[1]+egl[1])/2 + angle;

        } else {
            if (ableToPass())
            {
                // pass
                kickAngle = 0; // hogehoge
            } else {

                // dribble
                kickAngle = 0; // hogehoge
            }
        }

        elementList.push_back(new KickTo(w, kickAngle));
    } else {
        // hogehoge
        elementList.push_back(new RunTo(w, initpos));
    }
}


void Attack::updateFinishFlag(World& w) {
    finish_flag = false;
}


bool Attack::inTerritory(){
  if(abs(ballpos[0] - initpos[0]) < 6.0 &&
     abs(ballpos[1] - initpos[1]) < 6.0){
    return true;
  }else{
    return false;
  }
}

bool Attack::atHome(){
  if(abs(mypos[0] - initpos[0]) < 0.5 &&
     abs(mypos[1] - initpos[1]) < 0.5){
    return true;
  }else{
    return false;
  }
}

bool Attack::close2Bal(){
  if(abs(bal[0]) < 3){
    return true;
  }else{
    return false;
  }
}

bool Attack::hasBal() {
    if (abs(bal[0] < 0.7 &&
        abs(angle) <= 10))
    {
        return true;
    } else {
        return false;
    }
}

bool Attack::close2Goal() {
    if (((egr[0]+egl[0]) / 2) <= 7)
    {
        return true;
    } else {
        return false;
    }
}

bool Attack::ableToPass() {
    return true;
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

    // if (!tmpflag)
    // {
    //     elementList.push_back(new RunToBall(w));
    //     if (elementList.front()->isFinished())
    //     {
    //         tmpflag = true;
    //     }
    // } else {
    //     std::cout << "finish!!" << std::endl;
    //     elementList.push_back(new AdjustToBall(w));
    //     elementList.push_back(new KickTo(w, 0));
    //     elementList.push_back(new SequenceMovement("DUMMY"));
    // }

    // elementList.push_back(new TicktackBase("SLEFT", 10)); // migi ni mawarikomi

    kickAngle = (egr[1]+egl[1])/2 + angle;
    std::cout << "kick to" << kickAngle << std::endl;
    elementList.push_back(new KickTo(w, kickAngle));

    // std::cout << "judgement desu no!!" << std::endl;
    // std::cout << "next: " << typeid(*elementList.front()).name() << std::endl;
}
