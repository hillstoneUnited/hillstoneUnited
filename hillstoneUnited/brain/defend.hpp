#ifndef DEFEND_H
#define DEFEND_H

#include <sstream>

#include "brainbase.hpp"
#include "../world.hpp"
#include "runto.hpp"
#include "kickto.hpp"
#include "runtoball.hpp"
#include "runtoenemy.hpp"
#include "adjusttoball.hpp"
#include "../movement/gabase.hpp"
#include "../movement/standup.hpp"
#include "../movement/odenswalk.hpp"
#include "../movement/ticktackbase.hpp"
#include "../movement/sequencemovement.hpp"

class Defend : public BrainBase
{
public:

   Defend(World& w, double _initpos[]);
  ~Defend(){};

  //  bool isFinished();
  virtual std::string getNextAngle(World& w);

private:
  double initpos[3];
  double ballpos[2];
  double mypos[2];
  double bal[3];
  double angle;
  double dist;

  int field_x;
  int field_y;

  int balposconf;
  int myposconf;
  int t_count;

  double friends[11][4];
  double enemy[11][4];

   bool beam_flag;
  //  std::string beam_msg;
  std::stringstream beam_msg;

  bool inTerritory();
  bool atHome();
  bool close2Bal();
  bool towardEnemy();
  bool inDanger();
  int getInvader();

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
