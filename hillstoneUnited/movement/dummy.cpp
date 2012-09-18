#include "dummy.h"

Dummy::Dummy(){
  
}

Dummy::~Dummy(){}


std::string Dummy::getNextAngle(Action& act, World& w){

  resetAngleMap();

  set(w, raj1, -100.0);
  set(w, laj1, -100.0);
  set(w, raj2, 0.0);
  set(w, laj2, 0.0);
  set(w, raj3, 90.0);
  set(w, laj3, -90.0);
  set(w, raj4, 90.0);
  set(w, laj4, -90.0);
  set(w, rlj1, 0.0, 0.01);
  set(w, llj1, 0.0, 0.01);
  set(w, rlj2, 0.0, 0.05);
  set(w, llj2, 0.0, 0.05);
  set(w, rlj3, 0.0, 0.02);
  set(w, llj3, 0.0, 0.02);
  set(w, rlj4, 0.0, 0.02);
  set(w, llj4, 0.0, 0.02);
  set(w, rlj5, 0.0, 0.02);
  set(w, llj5, 0.0, 0.02);
  set(w, rlj6, 0.0, 0.05);
  set(w, llj6, 0.0, 0.05);
  
  stepCount(act);

  return angleToString();
}
