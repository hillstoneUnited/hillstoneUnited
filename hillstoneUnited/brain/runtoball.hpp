#ifndef RUNTOBALL_H
#define RUNTOBALL_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"

class RunToBall : public BrainBase
{
public:
    RunToBall(World& w);
    ~RunToBall(){};

    bool isFinished(World& w);

private:
    double ballpos[2];

};

#endif