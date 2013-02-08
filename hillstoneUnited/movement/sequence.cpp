#include "sequence.hpp"
#include <iostream>

Sequence::Sequence()
{
    num = 0;
//    std::cout << "sequence counstructor : " << num << std::endl;
}

bool Sequence::addPose(Pose p){

    if(num >= MAX_NUM){
        std::cout << "sequence::addPose : sequence has MAX_NUM poses. cannot add any more" << std::endl;
        return false;
    }

    poses[num] = p;

    num = num++;

    return true;
}

bool Sequence::setPose(int n, Pose p){
    if(n >= num){
        std::cout << "sequence::setPose : setPose cannot add new number of pose" << std::endl;
        return true;
    }

    poses[n] = p;

    return true;
}

bool Sequence::clear(){
    num = 0;

    for(int i=0; i<MAX_NUM; i++){
        poses[i].clear();
    }

    return true;
}

int Sequence::getNum(){
    return num;
}

Pose Sequence::getPose(int i){
    if(i >= num){
        std::cout << "getPose : cannot get Pose from poses[larger than num]" << std::endl
                  << "temporary returns poses[0]" << std::endl;
        return poses[0];
    }

    return poses[i];
}
