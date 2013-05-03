#ifndef ADJUSTTOBALL_H
#define ADJUSTTOBALL_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"

class AdjustToBall : public BrainBase
{
public:
    AdjustToBall(World& w);
    ~AdjustToBall(){};

private:
  double ballpos[2];
  double conf_ballpos;
  double bal[2];
  double conf_bal;
  double x,y;
  double conf_XY;
  int t_count;

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
