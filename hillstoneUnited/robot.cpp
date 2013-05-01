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

  double initpos[2] = {0.0, 0.0};

  if (virgin)
  {
    mainbrain = new Attack(world, initpos);
    virgin = false;
  }else{

    if (mainbrain->isFinished())
    {
      delete mainbrain;
      mainbrain = new Attack(world, initpos);
      std::cout << "finish!!" << std::endl;
    }

  }
  return mainbrain->getNextAngle(world);


}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
