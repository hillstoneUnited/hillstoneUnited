#include "robot.h"

Robot::Robot(std::string teamname){
  world = new World;
  mm = new MovementManager();

  world.setTeamname(teamname);
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){

  return mm.nextStr(DUMMY, world);

}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
