#include "robot.hpp"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
  virgin = true;
  d = new Drawing();
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
//	if(world.confBXY()<200 || !world.isFalling()){
//		d->draw(world);
//	}
  world.update(msg);
  world.dump();

  if(world.confBXY() < 200 && !world.isFalling()){
    Drawing drawing;
    drawing.draw(world);
  }

  static double initpos0[3] = {-13.5,0.0, 0.0}; // keeper

  static double initpos1[3] = {-10.5,3.5, 0.0};
  static double initpos2[3] = {-10.5,0.0, 0.0};
  static double initpos3[3] = {-10.5,-3.5, 0.0};
  static double initpos4[3] = {-7.0,1.5, 0.0};
  static double initpos5[3] = {-7.0,-1.5, 0.0};

  static double initpos6[3] = {-8.0,1.5, 0.0};
  static double initpos7[3] = {-6.0,-1.5, 0.0};
  static double initpos8[3] = {-2.5,1.5, 0.0};
  static double initpos9[3] = {-0.2,0.03, -10.0};
  static double initpos10[3] = {-2.5,-1.5, 0.0};

  double tmpinit[11][3] = {0.0,0.0,0.0};
  for (int i = 0; i < 11; i++)
  {
    tmpinit[i][0] = -1-i;
    tmpinit[i][1] = sin(i);
    tmpinit[i][2] = 0;
  }

  /*

  mainbrain = new TestBrain(world, initpos9);
  if (mainbrain->isFinished())
  {
    delete mainbrain;
    mainbrain = new TestBrain(world, initpos9);
  }
  return mainbrain->getNextAngle(world);

  */

  
  if (world.getUnum() > 0){
    if (virgin){


      // int unum = world.getUnum();
      // double tmp[3] {tmpinit[unum][0], tmpinit[unum][1], tmpinit[unum][2]};
      // mainbrain = new Attack(world, tmp);

      switch(world.getUnum()){
      case 1:
	// mainbrain = new Defend(world, initpos0);
	// mainbrain = new TestBrain(world, initpos0);
	mainbrain = new Keeper(world, initpos0);
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
        mainbrain = new Keeper(world, initpos0);
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
