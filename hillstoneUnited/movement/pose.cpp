#include "pose.hpp"
#include <iostream>

Pose::Pose()
{
/*
    for(int i=0; i<22; i++){
        target[i] = 0;
    }

    gain = 0.05;
*/
    clear();
}

Pose::Pose(double value[]){
    for(int i=0; i<22; i++){
        target[i] = value[i];
    }

    gain = 0.05;
}

void Pose::clear(){
    for(int i=0; i<22; i++){
        target[i] = 0;
    }
    gain = 0.05;
}

void Pose::setTarget(int i, double v){
    target[i] = v;
}

void Pose::setGain(double v){
    gain = v;
}

double Pose::getGain(){
    return gain;
}

double* Pose::getTarget(){
    return target;
}

double Pose::getTarget(int i){
    if(i > 22){
        std::cout << "Pose:getTarget(i)  i > 22" << std::endl;
        return 0;
    }
    return target[i];
}

Pose& Pose::operator=(const Pose& obj){
    for(int i=0; i<22; i++){
        this->target[i] = obj.target[i];
    }
    this->gain = obj.gain;
    return *this;
}

