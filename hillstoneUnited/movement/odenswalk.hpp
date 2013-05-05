#ifndef ODENSWALK_H
#define ODENSWALK_H

#include "movementbase.hpp"
#include "../MakeWalk/makewalk.hpp"

class OdensWalk : public MovementBase
{
public:
    OdensWalk(double _dest[]);
    OdensWalk(std::string _name, double _offsetdist=0.0, double _offsetangle=0.0);
    OdensWalk(int _enemEnum, double _offsetdist=0.0, double _offsetangle=0.0);
    ~OdensWalk();

    bool set(jointID id, double velocity);
    // bool set(World& w, jointID id, double angle, double gain = 0.05);
    
    // void setAngle(World& w, double joint[]);
    void setAngle(World& w, double joint[], double velocity[]);

    std::string getNextAngle(World& w);
private:
    static const double DEGTORAD = M_PI/180.0;
    static const double RADTODEG = 180.0/M_PI;
    MakeWalk mw;
    double dest[2];
    double offset[3]; // kyokuzahyo, degree
    double joint[12];
    std::string name;
    int enemEnum;

    double distance;
    double rotation; //目標の向きとの角度差[rad]

    int conf;

    void paramChangeByName(World& w);
    bool wannaWalk(World& w);

};

#endif
