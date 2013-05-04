#ifndef KEEPER_H
#define KEEPER_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/gabase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/standup.hpp"

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
    bool beam_flag;
};

#endif
