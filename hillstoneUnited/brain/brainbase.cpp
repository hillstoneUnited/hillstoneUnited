#include "brainbase.hpp"

BrainBase::~BrainBase(){
  while (!elementList.empty()) {
    ElementBase* tmp = elementList.front();
    delete tmp;
    elementList.pop_front();
  }
}


std::string BrainBase::getNextAngle(World& w){
  if (!elementList.empty()) {
    /*** cheking part ***/
    if (!elementList.front()->isFinished())
    {
      std::string rtnAngle = elementList.front()->getNextAngle(w);
      return rtnAngle;
    }else{
      ElementBase* tmp = elementList.front();
      delete tmp;
      elementList.pop_front();

      if (!elementList.front()->isFinished())
      {
        std::string rtnAngle = elementList.front()->getNextAngle(w);
        return rtnAngle;
      }else{
        /*** thinking yourself!! ***/
        return "hogehoge in brainbase";
      }
    }
  }else{
    std::cout << "elementList is empty!!" << std::endl;
  }
}
