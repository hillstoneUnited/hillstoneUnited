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
  static double initpos0[3] = {-13.5,0.0, 0.0}; // keeper

  static double initpos1[3] = {-10.5,6.0, 0.0};
  static double initpos2[3] = {-10.5,0.0, 0.0};
  static double initpos3[3] = {-10.5,-6.0, 0.0};
  static double initpos4[3] = {-7.0,2.5, 0.0};
  static double initpos5[3] = {-7.0,-2.5, 0.0};

  static double initpos6[3] = {-3.0,2.5, 0.0};
  static double initpos7[3] = {-3.0,-2.5, 0.0};
  static double initpos8[3] = {-1.0,5.0, 0.0};
  static double initpos9[3] = {-0.5,0.0, 0.0};
  static double initpos10[3] = {-1.0,-5.0, 0.0};

  double tmpinit[11][3] = {0.0,0.0,0.0};
  for (int i = 0; i < 11; i++)
  {
    tmpinit[i][0] = -1-i;
    tmpinit[i][1] = sin(i);
    tmpinit[i][2] = 0;
  }

  if (world.getUnum() > 0){
    if (virgin){


      // int unum = world.getUnum();
      // double tmp[3] {tmpinit[unum][0], tmpinit[unum][1], tmpinit[unum][2]};
      // mainbrain = new Attack(world, tmp);

      switch(world.getUnum()){
      case 1:
        mainbrain = new Attack(world, initpos0);
        break;
      case 2:
        mainbrain = new Defend(world, initpos1);
        break;
      case 3:
        mainbrain = new Defend(world, initpos2);
        break;
      case 4:
        mainbrain = new Defend(world, initpos3);
        break;
      case 5:
        mainbrain = new Defend(world, initpos4);
        break;
      case 6:
        mainbrain = new Defend(world, initpos5);
        break;
      case 7:
        mainbrain = new Attack(world, initpos6);
        break;
      case 8:
        mainbrain = new Attack(world, initpos7);
        break;
      case 9:
        mainbrain = new Attack(world, initpos8);
        break;
      case 10:
        mainbrain = new Attack(world, initpos9);
        break;
      case 11:
        mainbrain = new Attack(world, initpos10);
        break;
      default:
        break;
      }
      virgin = false;
      
    }else{
      
      if (mainbrain->isFinished()){
      	delete mainbrain;

        // int unum = world.getUnum();
        // double tmp[3] {tmpinit[unum][0], tmpinit[unum][1], tmpinit[unum][2]};
        // mainbrain = new Attack(world, tmp);

      switch(world.getUnum()){
      case 1:
        mainbrain = new Attack(world, initpos0);
        break;
      case 2:
        mainbrain = new Defend(world, initpos1);
        break;
      case 3:
        mainbrain = new Defend(world, initpos2);
        break;
      case 4:
        mainbrain = new Defend(world, initpos3);
        break;
      case 5:
        mainbrain = new Defend(world, initpos4);
        break;
      case 6:
        mainbrain = new Defend(world, initpos5);
        break;
      case 7:
        mainbrain = new Attack(world, initpos6);
        break;
      case 8:
        mainbrain = new Attack(world, initpos7);
        break;
      case 9:
        mainbrain = new Attack(world, initpos8);
        break;
      case 10:
        mainbrain = new Attack(world, initpos9);
        break;
      case 11:
        mainbrain = new Attack(world, initpos10);
        break;
      default:
        break;
      }
	
        std::cout << "finish!!" << std::endl;
      }
      
    }
    return mainbrain->getNextAngle(world);
  } 
  return "";
}
  
std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
