#include "robot.hpp"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
  virgin = true;
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
  world.update(msg);
  world.dump();

  //std::cout << "(in robot.cpp)" << act.getName() << std::endl;

  /**
  brain.checkResponse(world);
  brain.updateList();
  if(brain.allListEmpty()){
      brain.think(world);
  }
  return brain.getString(world);
  **/
  //return "hogehoge in robot"; // I'll change it

  if (virgin)
  {
    samplebrain = new RunToBall(world);
    virgin = false;
  }else{

    if (samplebrain->isFinished(world))
    {
      delete samplebrain;
      samplebrain = new RunToBall(world);
    }

  }
  return samplebrain->getNextAngle(world);


}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
