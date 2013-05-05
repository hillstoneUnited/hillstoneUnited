#ifndef KEEPER_H
#define KEEPER_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/gabase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/standup.hpp"
#include "runto.hpp"

class Keeper : public BrainBase
{
public:
    Keeper(World& w, double _initpos[]);
    ~Keeper(){};

    std::string getNextAngle(World& w);

private:
    void updateFinishFlag(World& w);
    void judgement(World& w);
    void restore_position(World& w);
    int null_anglecount;
    double initpos[3];
    double bal[2];
    double conf_bal;
    double ballpos[2];
    double conf_ballpos;
    double x,y;
    double conf_XY;
    bool beam_flag;
    bool judge_stand;
};

#endif
