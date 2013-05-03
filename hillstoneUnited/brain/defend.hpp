#ifndef DEFEND_H
#define DEFEND_H

#include "brainbase.hpp"
#include "../world.hpp"
#include "runto.hpp"
#include "runtoball.hpp"
#include "runtoenemy.hpp"
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
  //  std::string getNextAngle(World& w);

private:
  //  bool beam_flag;
  double initpos[3];
  double ballpos[2];
  double mypos[2];
  double bal[3];
  double angle;

  int field_x;
  int field_y;

  int balposconf;
  int myposconf;

  bool inTerritory();
  bool atHome();
  bool close2Bal();
  bool towardEnemy();
  bool inDanger();

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
