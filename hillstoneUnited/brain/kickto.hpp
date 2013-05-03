#ifndef KICKTO_H
#define KICKTO_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "../movement/gabase.hpp"
#include "../movement/sequencemovement.hpp"
#include "../movement/ticktackbase.hpp"

class KickTo : public BrainBase
{
public:
    KickTo(World& w, double _target_angle);
    ~KickTo(){};


private:
  double target_angle;
  bool is_kicked;
  void updateFinishFlag(World& w);
  void judgement(World& w);
  void turn(World& w);

};

#endif
