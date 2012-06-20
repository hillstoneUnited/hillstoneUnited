#include "robot.h"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);

}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  static bool init = false;
  if(init == false){
    init = true;
    return "(init (unum 0)(teamname " + world.getTeamname() + "))";
  }


  return "";
}
