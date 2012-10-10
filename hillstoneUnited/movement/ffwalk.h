#ifndef FFWALK_H
#define FFWALK_H

#include "movementbase.h"
#include "../util.h"

class FFWalk : public MovementBase{
  public:
    FFWalk();
    ~FFWalk();

    std::string getNextAngle(Action& act, World& w, int& ts);
    
  private:
    /*
     * S1-6: joint
     *  angle: joint angle
     *  axis: the axis of rotation
     * L3,4,6: link; initial position(represented in a vector)
     * a,b: yugan vector
     * P: target vector
     */

    struct Joint {
      double angle[3];
      double axis[3];
    };

    Joint joints[6];

    double l3;
    double l4;
    double l6;

    double yuganA[3];
    double yuganB[3];

    struct Target{
      double point[3];
      double yuganA[3]; // represented in a vector {x,y,z}
      double yuganB[3]; // represented in a vector {x,y,z}
    };

    Target target;

    void inverseKinematics();
};

#endif
