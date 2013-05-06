#ifndef FOLLOW_H
#define FOLLOW_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"
#include "../movement/gabase.hpp"

class Follow : public BrainBase
{
public:
    Follow(World& w, double _offx, double _offy);
    ~Follow(){};

private:
  double ballpos[2];
  double conf_ballpos;
  double bal[2];
  double conf_bal;
  double x,y;
  double conf_XY;
  int t_count;

  double offx,offy;
  double offdist, offangle;

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
