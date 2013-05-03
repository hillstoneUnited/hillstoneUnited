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

  //  static double initpos[3] = {-10.5, 0.0, 0.0};
  static double initpos1[3] = {-10.5,-5.0, 0.0};
  static double initpos2[3] = {-10.5, 5.0, 0.0};
  static double initpos3[3] = {-10.5, 0.0, 0.0};

  if (virgin)
  {
<<<<<<< HEAD
    // // mainbrain = new Attack(world, initpos);
    //    mainbrain = new Defend(world, initpos);
    switch(world.getUnum()){
    case 1:
      mainbrain = new Defend(world, initpos1);
      break;
    case 2:
      mainbrain = new Defend(world, initpos2);
      break;
    default:
      mainbrain = new Defend(world, initpos3);
      break;
    }

    virgin = false;

  }else{

    if (mainbrain->isFinished())
    {
      delete mainbrain;
<<<<<<< HEAD
      // mainbrain = new Attack(world, initpos);
      //      mainbrain = new Defend(world, initpos);
      switch(world.getUnum()){
      case 1:
	mainbrain = new Defend(world, initpos1);
	break;
      case 2:
	mainbrain = new Defend(world, initpos2);
	break;
      default:
	mainbrain = new Defend(world, initpos3);
	break;
      }

      std::cout << "finish!!" << std::endl;
    }

  }
  return mainbrain->getNextAngle(world);


}

std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
