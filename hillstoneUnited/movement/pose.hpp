#ifndef POSE_H
#define POSE_H

class Pose
{
private:
    //target angle
    //order
    //hj1,2
    //laj1,raj1 laj2,raj2 ...
    //llj1,rlj1 llj2,rlj2 ...
    double target[22];

    double gain;

public:
    Pose();
    Pose(double value[22]);

    void clear();
    void setTarget(int i, double v);
    void setGain(double v);
    double getGain();
    double* getTarget();
    double getTarget(int i);

    Pose& operator=(const Pose& obj);
};

#endif // POSE_H
