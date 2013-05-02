#ifndef RUNTO_H
#define RUNTO_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"

class RunTo : public BrainBase
{
public:
  RunTo(World& w, double _point[]);
    ~RunTo(){};

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
