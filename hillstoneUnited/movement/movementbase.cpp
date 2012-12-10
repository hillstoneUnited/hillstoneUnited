#include "movementbase.hpp"

bool MovementBase::set(World& w, jointID id, 
    double angle, double gain){
  const double EPS = 0.2; // just like margin of error
  double current = 0.0;

  switch(id){
    case hj1: current = w.getAngle("hj1");break;
    case hj2: current = w.getAngle("hj2");break;
    case laj1: current = w.getAngle("laj1");break;
    case raj1: current = w.getAngle("raj1");break;
    case laj2: current = w.getAngle("laj2");break;
    case raj2: current = w.getAngle("raj2");break;
    case laj3: current = w.getAngle("laj3");break;
    case raj3: current = w.getAngle("raj3");break;
    case laj4: current = w.getAngle("laj4");break;
    case raj4: current = w.getAngle("raj4");break;
    case llj1: current = w.getAngle("llj1");break;
    case rlj1: current = w.getAngle("rlj1");break;
    case llj2: current = w.getAngle("llj2");break;
    case rlj2: current = w.getAngle("rlj2");break;
    case llj3: current = w.getAngle("llj3");break;
    case rlj3: current = w.getAngle("rlj3");break;
    case llj4: current = w.getAngle("llj4");break;
    case rlj4: current = w.getAngle("rlj4");break;
    case llj5: current = w.getAngle("llj5");break;
    case rlj5: current = w.getAngle("rlj5");break;
    case llj6: current = w.getAngle("llj6");break;
    case rlj6: current = w.getAngle("rlj6");break;
    default:
      std::cout << "Cannot find ID : " << id << std::endl;
      break;
  }

  if(fabs(current - angle) > EPS){
    angleMap[id] = gain * (angle - current);
    return true;
  }

  angleMap[id] = 0.0;
  return false;
}

std::string MovementBase::angleToString(){
  std::string jointName[] = {
    "he1", "he2",
    "lae1", "rae1", "lae2", "rae2", "lae3", "rae3", "lae4", "rae4",
    "lle1", "rle1", "lle2", "rle2", "lle3", "rle3",
    "lle4", "rle4", "lle5", "rle5", "lle6", "rle6"
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
