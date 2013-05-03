#include "attack.hpp"

Attack::Attack(World& w, double _initpos[]) {
    finish_flag = false;
    beam_flag = false;

    ballpos[0] = 0.0;
    ballpos[1] = 0.0;
    bal[0] = w.getBAL(0);
    bal[1] = w.getBAL(1);
    bal[2] = w.getBAL(2);
    mypos[0] = 0.0;
    mypos[1] = 0.0;
    balposconf = w.confBAL();
    myposconf = w.confXY();
    egrconf = w.confEGR();
    eglconf = w.confEGL();
    angle = w.getABSANGLE();
    for (int i = 0; i < 3; i++)
    {
        egr[i] = w.getEGR(i);
        egl[i] = w.getEGL(i);
    }
    updateFandE(w);

    field_x = w.getFieldLengthX();
    field_y = w.getFieldLengthY();

    kickAngle = 0.0;
    passTo = 0;

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
    egrconf = w.confEGR();
    eglconf = w.confEGL();
    angle = w.getABSANGLE();
    for (int i = 0; i < 3; i++)
    {
        egr[i] = w.getEGR(i);
        egl[i] = w.getEGL(i);
    }
    updateFandE(w);

    kickAngle = 0.0;
    passTo = 0;

    std::cout << egr[0] << std::endl;
    std::cout << egr[1] << std::endl;


    if (hasBal())
    {
        if (close2Goal())
        {
            // shoot
            kickAngle = (egr[1]+egl[1])/2 + angle;
            std::cout << "shoot!! to " << kickAngle <<std::endl;

        } else {
            std::cout << "pass?" << ableToPass() << std::endl;
            if (ableToPass())
            {
                // pass
                kickAngle = friends[passTo][1] + angle; // hogehoge
                std::cout << "pass to " << kickAngle <<std::endl;
            } else {

                // dribble
                kickAngle = 0; // hogehoge
                std::cout << "dribble to " << kickAngle << std::endl;
            }
        }

        elementList.push_back(new KickTo(w, kickAngle));
    } else {
        // hogehoge
        elementList.push_back(new RunTo(w, initpos));
    }

    // testJudge(w);
}


void Attack::updateFinishFlag(World& w) {
    finish_flag = false;
}

void Attack::updateFandE(World& w) {
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            friends[i][j] = w.getFRIEND(i, j);
            enemies[i][j] = w.getENEMY(i, j);
            std::cout << friends[i][j] << ", ";
        }
        friendsconf[i] = w.confFRIEND(i);
        enemiesconf[i] = w.confENEMY(i);
        std::cout << friendsconf[i] << ", " << std::endl;
    }
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
    if (((egr[0]+egl[0]) / 2) <= 7 &&
        egrconf <= 250 && eglconf <= 250)
    {
        return true;
    } else {
        return false;
    }
}

bool Attack::ableToPass() {

    double distanceToFriend = 10000.0;
    bool pass_flag = false;

    for (int i = 0; i < 11; i++)
    {
        if (friendsconf[i] <= 100 &&
            abs(angle + friends[i][1]) <= 45 &&
            friends[i][0] >= 2.5 &&
            friends[i][0] <= distanceToFriend)
        {
            passTo = i;
            distanceToFriend = friends[i][0];
            pass_flag = true;
        }
    }

    return pass_flag;
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

    elementList.clear();
    kickAngle = (egr[1]+egl[1])/2 + angle;
    std::cout << "kick to" << kickAngle << std::endl;
    elementList.push_back(new KickTo(w, kickAngle));

    // std::cout << "judgement desu no!!" << std::endl;
    // std::cout << "next: " << typeid(*elementList.front()).name() << std::endl;
}


std::string Attack::getNextAngle(World& w) {
  std::stringstream ss;
  if(w.getPlaymode()=="BeforeKickOff"&&w.getUnum()>0){
    beam_flag = true;
    ss << "(beam " << initpos[0] << " "
       << initpos[1] << " " << initpos[2]
       << ")";
    //    std::cout << ss.str() << std::endl;
  }

    if (w.isFalling())
    {
        if (!pushStand)
        {
            elementList.clear();
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
        rtn = elementList.front()->getNextAngle(w);
        if (elementList.empty())
        {
            updateFinishFlag(w);
        }
        
        if(beam_flag){
          rtn += ss.str();
          beam_flag = false;
        }

        return rtn;
    }

    pushStand = false;

    if (!elementList.empty())
    {
        if (!elementList.front()->isFinished())
        {
            rtn = elementList.front()->getNextAngle(w);
            if(beam_flag){
                rtn += ss.str();
                beam_flag = false;
            }
            return rtn;
        } else {
            ElementBase* tmp = elementList.front();
            delete tmp;
            elementList.pop_front();

            if (!elementList.empty())
            {
            } else {
                judgement(w);
            }
            rtn = elementList.front()->getNextAngle(w);
            if (elementList.empty())
            {
                updateFinishFlag(w);
            }
        if(beam_flag){
          rtn += ss.str();
          beam_flag = false;
        }
            return rtn;
        }
    } else {
        judgement(w);
        rtn = elementList.front()->getNextAngle(w);
        if (elementList.empty())
        {
            updateFinishFlag(w);
        }
        if(beam_flag){
            rtn += ss.str();
            beam_flag = false;
        }
        return rtn;
    }
}
