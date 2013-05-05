#ifndef ODENSWALK_H
#define ODENSWALK_H

#include "movementbase.hpp"
#include "../MakeWalk/makewalk.hpp"

class OdensWalk : public MovementBase
{
public:
    OdensWalk(std::string _name, double _dest[], int _uptime=1000);
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
    double joint[12];
    std::string name;

    int t;
    int uptime;
};

#endif
