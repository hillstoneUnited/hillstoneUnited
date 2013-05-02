#ifndef RUNTOENEMY_H
#define RUNTOENEMY_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/gabase.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/standup.hpp"

class RunToEnemy : public BrainBase
{
public:
  RunToEnemy(World& w, int _enemy_unum);
    ~RunToEnemy(){};

    // bool isFinished(World& w);

private:
  double enemy[2];
  double conf_enemy;
  int t_count;
  int enemy_unum;

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
