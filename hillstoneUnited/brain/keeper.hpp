#ifndef KEEPER_H
#define KEEPER_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/gabase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/ticktackbase.hpp"

class Keeper : public BrainBase
{
public:
    Keeper(World& w);
    ~Keeper(){};


private:
  void updateFinishFlag(World& w);
  void judgement(World& w);

};

#endif
