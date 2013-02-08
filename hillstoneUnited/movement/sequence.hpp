#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "pose.hpp"

/*
  Sequence class.
  This class holds pose information.
  Robot poses sequentially (ex. stand -> stand by one leg -> kick out other leg)
  Even one pose action, it will be written as sequence class (and its pose number is 1).
 */


class Sequence
{
public:
    Sequence();

    // bool -> true:succeed  false:failed
    bool addPose(Pose p); // add "p" in poses[num] and update num
    bool setPose(int n, Pose p); // overwrite poses[n-1] by "p"
    bool clear(); // clear poses and reset number
    int getNum(); // get how many poses the sequence has
    Pose getPose(int i); // get poses[i] .  checked not to access poses[larger_than_num]

private:
    static const int MAX_NUM = 10;
    int num; // number of using pose. 0 in initialized(and meaning poses[] is empty). max is MAX_NUM (but should not access poses[MAX_NUM])
    Pose poses[MAX_NUM]; // hold space. when sequence has X poses(num = X), poses[] is used poses[0]...poses[X-1]
};

#endif // SEQUENCE_H
