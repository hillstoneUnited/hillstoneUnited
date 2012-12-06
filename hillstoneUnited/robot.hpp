#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include "world.hpp"
#include "brain.hpp"

/*
  This class is interface to main function.
  This class receive string from server(include what the robot sensor observed).
  And return message to server(include how the robot want to move his joint).
  Process (ex.interpret string, decide action, calculate joint angle) is subclass's task, so this class has few work.
 */
class Robot{
 public:
  Robot(std::string teamname);
  ~Robot();

  std::string Init(){
    // inform server to use nao model
    return "(scene rsg/agent/nao/nao.rsg)";
  }

  std::string Init2(); // send teamname

  std::string getNextAngle(std::string &msg);

 protected:
  World world;
  Brain brain;

};

#endif
