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

  static double initpos[3] = {-10.5, 0.0, 0.0};

  if (virgin)
  {
    //mainbrain = new Attack(world, initpos);
    //mainbrain = new Defend(world, initpos);
    //mainbrain = new KickTo(world, 90);
    mainbrain = new Keeper(world);
    virgin = false;
  }else{

    if (mainbrain->isFinished())
    {
      delete mainbrain;
      //mainbrain = new Attack(world, initpos);
      mainbrain = new Keeper(world);
      //mainbrain = new Defend(world, initpos);
      //mainbrain = new KickTo(world, 90);
      std::cout << "finish!!" << std::endl;
    }

  }
  return mainbrain->getNextAngle(world);


}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
