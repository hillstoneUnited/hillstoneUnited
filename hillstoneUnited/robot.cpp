#include "robot.h"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
  Action act;
  Action act2(DUMMY);

  return mm.nextStr(act2, world);

}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
