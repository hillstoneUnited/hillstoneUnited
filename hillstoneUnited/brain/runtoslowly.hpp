#ifndef RUNTOSLOWLY_H
#define RUNTOSLOWLY_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"

class RunToSlowly : public BrainBase
{
public:
  RunToSlowly(World& w, double _point[]);
    ~RunToSlowly(){};

    // bool isFinished(World& w);

private:
  double point[2];
  double conf_enemy;
  int t_count;
  double x, y;
  int conf_XY;
  double dist;
  double my_angle;
  double angle;
  double u, v;

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
