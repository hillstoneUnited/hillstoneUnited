#include "robot.h"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
  world.update(msg);
  world.dump();

  //std::cout << "(in robot.cpp)" << act.getName() << std::endl;
  brain.update(world);
  return brain.getString(world);

}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
