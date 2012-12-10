#include "brainbase.hpp"

BrainBase::~BrainBase(){
  while (!elementList.empty()) {
    ElementBase* tmp = elementList.pop_front();
    delete tmp;
  }
}


std::string BrainBase::getNextString(World& w){
  if (!elementList.empty()) {
    if (!elementList.front()->isFinished()) {
      std::string returnAngle = elementList.front()->getNextString(World& w);
      return returnAngle;
    }else{
      ElementBase* tmp = elementList.pop_front();
      delete tmp;
    }
  }else{
    std::cout << "elementList is empty!!" << std::endl;
  }
}
