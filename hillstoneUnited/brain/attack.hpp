#ifndef ATTACK_H
#define ATTACK_H

#include <typeinfo>

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/standup.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "runtoball.hpp"
#include "adjusttoball.hpp"
#include "kickto.hpp"
#include "runto.hpp"

class Attack : public BrainBase
{
public:
    Attack(World& w, double _initpos[]);
    ~Attack(){};

    // bool isFinished();
    // std::string getNextAngle(World& w);

private:
    double initpos[3];
    double ballpos[2];
    double mypos[2];
    double bal[3];
    double angle;
    double egr[3];
    double egl[3];
    double friends[11][3];

    int field_x;
    int field_y;

    int balposconf;
    int myposconf;
    int egrconf;
    int eglconf;
    int friendsconf[11];

    double kickAngle;
    int passTo;

    bool tmpflag;

    void judgement(World& w);
    void updateFinishFlag(World& w);

    void testJudge(World& w);

    void updateFriends(World& w);

    bool inTerritory();
    bool atHome();
    bool close2Bal();
    bool hasBal();
    bool close2Goal();
    bool ableToPass();
};

#endif
