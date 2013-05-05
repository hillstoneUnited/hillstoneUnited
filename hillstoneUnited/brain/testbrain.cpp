#include "testbrain.hpp"

TestBrain::TestBrain(World& w, double _initpos[]) {
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
    ROLE = "NONE";

    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
    initpos[2] = _initpos[2];
    judgement(w);
}

void TestBrain::judgement(World& w) {

    ballpos[0] = w.getBXY_AVE(0);
    ballpos[1] = w.getBXY_AVE(1);
    bal[0] = w.getBAL(0);
    bal[1] = w.getBAL(1);
    bal[2] = w.getBAL(2);
    mypos[0] = w.getXY_AVE(0);
    mypos[1] = w.getXY_AVE(1);
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

    double offset[2] = {0.0,0.0};

    if (w.confXY() == 300 || w.confBXY() == 300)
    {
        // elementList.push_back(new TicktackBase("TLEFT", 5));
        elementList.push_back(new SequenceMovement("LAROUND"));
    }

    if (w.getPlaymode()=="BeforeKickOff")
    {
        elementList.push_front(new SequenceMovement("DUMMY"));
    }
    static bool kick_flag;

    switch(w.getUnum()){
        case 10:
        offset[0] = 3.0;
        offset[1] = 0.0;
        if(w.getPlaymode()=="BeforeKickOff"){
          kick_flag = true;
        }
        if(w.getPlaymode()=="KickOff_Left" && kick_flag == true){
          elementList.push_front(new GABase("GA_FORWARD", 100));
          kick_flag = false;
        }
        if (fabs(w.getFRIEND(2, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(2, 1) - bal[1]) <= 50 &&
            w.confFRIEND(2) <= 200)
        {
            ROLE = "FOLLOW";
        } else if (fabs(w.getFRIEND(3, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(3, 1) - bal[1]) <= 50 &&
            w.confFRIEND(3) <= 200) {
            ROLE = "FOLLOW";
        } else {
            ROLE = "TOP";
        }
        break;

        case 9:
        offset[0] = 2.0;
        offset[1] = 2.0;
        if(w.getPlaymode()=="KickOff_Left" && kick_flag == true){
          elementList.push_front(new Kick());
          kick_flag = false;
        }
        if (fabs(w.getFRIEND(1, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(1, 1) - bal[1]) <= 50 &&
            w.confFRIEND(1) <= 200)
        {
            ROLE = "FOLLOW";
        } else if (fabs(w.getFRIEND(3, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(3, 1) - bal[1]) <= 50 &&
            w.confFRIEND(3) <= 200) {
            ROLE = "FOLLOW";
        } else {
            ROLE = "TOP";
        }
        break;

        case 11:
        offset[0] = 3.0;
        offset[1] = -1.0;
        if(w.getPlaymode()=="KickOff_Left" && kick_flag == true){
          elementList.push_front(new Kick());
          kick_flag = false;
        }
        if (fabs(w.getFRIEND(2, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(2, 1) - bal[1]) <= 50 &&
            w.confFRIEND(2) <= 200)
        {
            ROLE = "FOLLOW";
        } else if (fabs(w.getFRIEND(1, 0) - bal[0]) <= bal[0] &&
            fabs(w.getFRIEND(1, 1) - bal[1]) <= 50 &&
            w.confFRIEND(1) <= 200) {
            ROLE = "FOLLOW";
        } else {
            ROLE = "TOP";
        }
        break;

        case 7:

        ROLE = "MF";

        break;

        case 8:

        ROLE = "MF";

        break;

    }

    if (ROLE=="TOP")
    {
        elementList.push_back(new AdjustToBall(w));
        elementList.push_back(new TicktackBase("FORWARD", 3));
        elementList.push_back(new GABase("GA_FORWARD", 100));   
    } else if (ROLE=="FOLLOW") {
        double send[2] = {ballpos[0]+offset[0], ballpos[1]+offset[1]};
        elementList.push_back(new OdensWalk(offset));
    } else if (ROLE=="MF") {
        if (inTerritory() || hasBal() || close2Bal())
        {
            elementList.push_back(new AdjustToBall(w));
            elementList.push_back(new TicktackBase("FORWARD", 3));
            elementList.push_back(new GABase("GA_FORWARD", 70));
        } else {
            elementList.push_back(new RunTo(w, initpos));
        }
    }

    judgeStandup(w);

}

void TestBrain::updateFinishFlag(World& w) {
    judgement(w);
}

void TestBrain::updateFandE(World& w) {
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


bool TestBrain::inTerritory(){
  if(fabs(ballpos[0] - initpos[0]) < 2.0 &&
     fabs(ballpos[1] - initpos[1]) < 2.0 &&
     balposconf <= 250){
    return true;
  }else{
    return false;
  }
}

bool TestBrain::atHome(){
  if(abs(mypos[0] - initpos[0]) < 3 &&
     abs(mypos[1] - initpos[1]) < 3){
    return true;
  }else{
    return false;
  }
}

bool TestBrain::farHome() {
    if (sqrt(pow(mypos[0]-initpos[0], 2.0) +
             pow(mypos[1]-initpos[1], 2.0)) >= 10 &&
        myposconf <= 250)
    {
        return true;
    } else {
        return false;
    }
}

bool TestBrain::close2Bal(){
  if(abs(bal[0]) < 3 && balposconf <= 150){
    return true;
  }else{
    return false;
  }
}

bool TestBrain::hasBal() {

    if (bal[0] < 2 &&
        abs(bal[1]) <= 10 &&
        balposconf <= 150)
    {
        return true;
    } else {
        return false;
    }
}

bool TestBrain::close2Goal() {
    if (((egr[0]+egl[0]) / 2) <= 7 &&
        egrconf <= 250 && eglconf <= 250)
    {
        return true;
    } else {
        return false;
    }
}

bool TestBrain::ableToPass() {

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


int TestBrain::getInvader(){
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

std::string TestBrain::getNextAngle(World& w) {
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

    // if (w.isFalling())
    // {
    //     if (pushStand)
    //     {
    //         /* code */
    //     } else {
    //         std::cout << "elementList clear" << std::endl;
    //         while(!elementList.empty()) {
    //             ElementBase* tmp = elementList.front();
    //             delete tmp;
    //             elementList.pop_front();
    //         }
    //         elementList.push_front(new Standup());
    //         pushStand = true;
    //     }
    // } else {
    //     pushStand = false;
    // }

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
