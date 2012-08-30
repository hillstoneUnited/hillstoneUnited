#ifndef MOVEMENTBASE_H
#define MOVEMENTBASE_H

#include <iostream>
#include <map>
#include <sstream>
#include <math.h>
#include "../util.h"
#include "../world.h"
#include "../action.h"

  class MovementBase{

    public:
      MovementBase();
      ~MovementBase();
      
      virtual std::string getNextAngle(Action act, World& w) = 0;
        //return the next angle

    protected:
      typedef std::map<jointID, double> tmpAngleMap;
      tmpAngleMap angleMap;

      bool set(World& w, jointID id, double angle, double gain = 0.05);

      std::string angleToString();
        // transrate the own angle map to string

      void resetAngleMap();
        // put 0 into each angle map. It must be called every step

  };

#endif
