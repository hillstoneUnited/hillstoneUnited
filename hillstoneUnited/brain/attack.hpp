#ifndef ATTACK_H
#define ATTACK_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"

class Attack : public BrainBase
{
public:
    Attack(World& w, double _initpos[]);
    ~Attack(){};

    bool isFinished();
    std::string getNextAngle(World& w);

private:
    double initpos[2];
};

#endif
