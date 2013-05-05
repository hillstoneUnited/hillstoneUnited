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

    judgeStandup(w);

    // std::cout << egr[0] << std::endl;
    // std::cout << egr[1] << std::endl;


    if (hasBal())
    {
        if (close2Goal())
        {
            // shoot
            kickAngle = (egr[1]+egl[1])/2 + angle;
            // std::cout << "shoot!! to " << kickAngle <<std::endl;

        } else {
            // std::cout << "pass?" << ableToPass() << std::endl;
            if (ableToPass())
            {
                // pass
                kickAngle = friends[passTo][1] + angle; // hogehoge
                // std::cout << "pass to " << kickAngle <<std::endl;
            } else {

                // dribble
                kickAngle = 0; // hogehoge
                // std::cout << "dribble to " << kickAngle << std::endl;
            }
        }

        elementList.push_back(new AdjustToBall(w));
        elementList.push_back(new KickToFront(w));
    } else {
        if (farHome())
        {
            elementList.push_back(new RunTo(w, initpos));
            // std::cout << "go home" << std::endl;
        } else {
            int invader = getInvader();
            if (invader != -1)
            {
                elementList.push_back(new RunToEnemy(w, invader));
                // std::cout << "tuckle" << std::endl;
            } else {
                if (close2Bal() || inTerritory())
                {
                    if (bal[0] < 1.5)
                    {
                        elementList.push_back(new AdjustToBall(w));
                        // std::cout << "#attack: adjusting" << std::endl;
                    } else {
                        elementList.push_back(new RunToBall(w));
                        // std::cout << "ball!!" << std::endl;
                    }
                } else {
                    elementList.push_back(new RunTo(w, initpos));
                    // std::cout << "go home(nothing)" << std::endl;
                }
            }
        }
    }
}


void Attack::updateFinishFlag(World& w) {
    judgement(w);
}

void Attack::updateFandE(World& w) {
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            friends[i][j] = w.getFRIEND(i, j);
            enemies[i][j] = w.getENEMY(i, j);
            // std::cout << friends[i][j] << ", ";
        }
        friendsconf[i] = w.confFRIEND(i);
        enemiesconf[i] = w.confENEMY(i);
        // std::cout << friendsconf[i] << ", " << std::endl;
    }
}


bool Attack::inTerritory(){
  if(abs(ballpos[0] - initpos[0]) < 6.0 &&
     abs(ballpos[1] - initpos[1]) < 6.0 &&
     balposconf <= 250){
    return true;
  }else{
    return false;
  }
}

bool Attack::atHome(){
  if(abs(mypos[0] - initpos[0]) < 3 &&
     abs(mypos[1] - initpos[1]) < 3){
    return true;
  }else{
    return false;
  }
}

bool Attack::farHome() {
    if (sqrt(pow(mypos[0]-initpos[0], 2.0) +
             pow(mypos[1]-initpos[1], 2.0)) >= 10 &&
        myposconf <= 250)
    {
        return true;
    } else {
        return false;
    }
}

bool Attack::close2Bal(){
  if(abs(bal[0]) < 4.5 && balposconf <= 150){
    return true;
  }else{
    return false;
  }
}

bool Attack::hasBal() {

    if (bal[0] < 2 &&
        abs(bal[1]) <= 10 &&
        balposconf <= 150)
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


int Attack::getInvader(){
    for (int i = 10; i >= 0; i--)
    {
        if (abs(enemies[i][0] - ballpos[0]) < 1.0 &&
            abs(enemies[i][1] - ballpos[1]) < 10 &&
            enemiesconf[i] <= 50)
        {
            return i;
        }
    }

    return -1; // should not to tuckle
}

std::string Attack::getNextAngle(World& w) {
    std::stringstream ss;
    if((w.getPlaymode()=="BeforeKickOff" ||
       w.getPlaymode()=="Goal_Left" ||
       w.getPlaymode()=="Goal_Right") && w.getUnum()>0){
        beam_flag = true;
        ss << "(beam " << initpos[0] << " "
                << initpos[1] << " " << initpos[2]
                << ")";
        // std::cout << ss.str() << std::endl;
    }

    if (w.isFalling())
    {
        if (pushStand)
        {
            /* code */
        } else {
            while(!elementList.empty())
            {
                ElementBase* tmp = elementList.front();
                delete tmp;
                elementList.pop_front();
            }
            elementList.push_front(new Standup());
            pushStand = true;
        }
    } else {
        pushStand = false;
    }

    rtn = elementList.front()->getNextAngle(w);
    if(beam_flag){
        rtn += ss.str();
        beam_flag = false;
    }
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
}
