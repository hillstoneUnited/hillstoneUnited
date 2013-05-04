#ifndef KICKTOFRONT_H
#define KICKTOFRONT_H

#include "brainbase.hpp"
#include "../world.hpp"

#include "brain/runto.hpp"

#include "../movement/gabase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/ticktackbase.hpp"

class KickToFront : public BrainBase
{
public:
    KickToFront(World& w);
    ~KickToFront(){};


private:
  void updateFinishFlag(World& w);
  void judgement(World& w);
  int modanglecount;

};

#endif
