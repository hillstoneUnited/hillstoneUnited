#ifndef ATTACK_H
#define ATTACK_H

#include <typeinfo>

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"

class Attack : public BrainBase
{
public:
    Attack(World& w, double _initpos[]);
    ~Attack(){};

    bool isFinished();
    std::string getNextAngle(World& w);

private:
    double initpos[2];
    bool tmpflag;

    void judgement(World& w);
};

#endif
