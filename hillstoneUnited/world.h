#ifndef WORLD_H
#define WORLD_H

#include <iostream>

/*
  World class hold sensor data.
  parse string from server, and hold included data(ex.object seen, gyro sensor).
 */
class World{
 public:
  World();
  ~World();

  void setTeamname(std::string name);
  std::string getTeamname();

 private:
  std::string teamname;

};

#endif
