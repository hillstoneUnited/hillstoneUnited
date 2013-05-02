#ifndef RUNTOBALL_H
#define RUNTOBALL_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"

class RunToBall : public BrainBase
{
public:
    RunToBall(World& w);
    ~RunToBall(){};

    // bool isFinished();
    // std::string getNextAngle(World& w);

private:
  double ballpos[2];
  double conf_ballpos;
  double bal[2];
  double conf_bal;
  double x,y;
  double conf_XY;
  double temp_abs;
  int t_count;

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
