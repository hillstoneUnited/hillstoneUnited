#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "rcss3dsocket.hpp"
#include "robot.hpp"

int main(int argc, char* argv[]){
  int port = 3100;
  std::string host = "127.0.0.1";
  std::string teamname = "HillstoneUnited";

  std::cout << "\"" << teamname << "\", a \"agentspark\" distribution." << std::endl
	    << "Copylight (C) 2012 " << teamname << " development team." << std::endl
	    << "2004 RoboCup Soccer Server 3D Maintenance Group." << std::endl << std::endl;

  //check argument
  for(int i=0; i<argc; i++){
    if(strcmp(argv[i], "--help") == 0){
      //printhelp();
      exit(0);
    }else if(strncmp(argv[i], "--host", 6) == 0){
      std::string tmp = argv[i];
      if(tmp.length() <= 7){
	//printhelp();
	exit(0);
      }
      host = tmp.substr(7);
    }else if(strncmp(argv[i], "--team", 6) == 0){
      std::string tmp = argv[i];
      if(tmp.length() <= 7){
	//printhelp();
	exit(0);
      }
      teamname = tmp.substr(7);
    }
  }

  //make socket
  rcss3dSocket soc;
  if(soc.Connect(port, host) == false){
    std::cout << "main: connect failed. exit program" << std::endl;
    exit(1);
  }

  //make robot and initializing
  Robot robo(teamname);
  soc.PutMessage(robo.Init()); // send server "use nao model"
  {
    std::string temp;
    soc.GetMessage(temp); // throw away message
  }
  soc.PutMessage(robo.Init2()); // send server "I'm team foobar"


  //Running loop
  while(1){ // use signal (or something) to stop running
    std::string msg;
    soc.GetMessage(msg);
    soc.PutMessage(robo.getNextAngle(msg));
  }

  //destloy socket and robot

  return 0;
}
