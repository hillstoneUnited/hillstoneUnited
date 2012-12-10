#include "elementbase.hpp"

ElementBase;;ElementBase(){
  finish_flag = false;
}

bool ElementBase::isFinished(){
  return finish_flag;
}
