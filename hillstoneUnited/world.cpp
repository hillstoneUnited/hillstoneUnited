#include "world.h"

World::World(){

}

World::~World(){}

void World::setTeamname(std::string name){
  teamname = name;
  return;
}

std::string World::getTeamname(){
  return teamname;
}

