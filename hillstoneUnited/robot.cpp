#include "robot.h"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
  world.update(msg);
  world.dump();


  //Action act;
  //Action act2(DUMMY);
  Action act = bm.getAct(world);

  return mm.nextStr(act, world);


}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
