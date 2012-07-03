#include "movementbase.h"

MovementBase::MovementBase(){
  
}

MovementBase::~MovementBase(){}

std::string MovementBase::angleToString(){
  std::string jointName[] = {
    "he1", "he2",
    "lae1", "lae2", "lae3", "lae4",
    "lle1", "lle2", "lle3", "lle4", "lle5", "lle6",
    "rae1", "rae2", "rae3", "rae4",
    "rle1", "rle2", "rle3", "rle4", "rle5", "rle6"
  };

  tmpAngleMap::iterator i;
  std::stringstream ss;
  int j;

  i = angleMap.begin();
  j = 0;

  while(i != angleMap.end()){
    ss << "(" << jointName[j] << " " << i->second << ")";
    i++;
    j++;
  }
  return ss.str();
}

void MovementBase::resetAngleMap(){
  angleMap.clear();

  angleMap[hj1] = 0.0;
  angleMap[hj2] = 0.0;

  angleMap[laj1] = 0.0;
  angleMap[raj1] = 0.0;
  angleMap[laj2] = 0.0;
  angleMap[raj2] = 0.0;
  angleMap[laj3] = 0.0;
  angleMap[raj3] = 0.0;
  angleMap[laj4] = 0.0;
  angleMap[raj4] = 0.0;

  angleMap[llj1] = 0.0;
  angleMap[rlj1] = 0.0;
  angleMap[llj2] = 0.0;
  angleMap[rlj2] = 0.0;
  angleMap[llj3] = 0.0;
  angleMap[rlj3] = 0.0;
  angleMap[llj4] = 0.0;
  angleMap[rlj4] = 0.0;
  angleMap[llj5] = 0.0;
  angleMap[rlj5] = 0.0;
  angleMap[llj6] = 0.0;
  angleMap[rlj6] = 0.0;
}
