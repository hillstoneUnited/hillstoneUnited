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
#include "../movement/kick.hpp"
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
  double bal[3];
  double xy[2];
  double bxy[2];
  double angle;
  double dist;

  int field_x;
  int field_y;

  int bal_conf;
  int bxy_conf;
  int xy_conf;
  int t_count;

  double friends[11][4];
  double enemy[11][4];
  int friends_conf[11];
  int enemy_conf[11];

   bool beam_flag;
  bool start_flag;
  //  std::string beam_msg;
  std::stringstream beam_msg;

  bool inTerritory();
  bool atHome();
  bool close2Bal();
  bool towardEnemy();
  bool inDanger();
  int getInvader();
  int getFriendsNearBall();
  void check();

  void judgement(World& w);
  void updateFinishFlag(World& w);

};

#endif
