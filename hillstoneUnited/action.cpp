#include "action.h"

Action::Action(ActionName _name, int _count){
  name = _name;
  count = _count;
  finished = false;
  lock = false;
  priority = 0;
}

Action::~Action(){}

void Action::setName(ActionName _name){
  name = _name;
}

ActionName Action::getName(){
  return name;
}

void Action::setCount(int _count){
  count = _count;
}

int Action::getCount(){
  return count;
}

void Action::setFinished(bool _finished){
  finished = _finished;
}

bool Action::isFinished(){
  return finished;
}

void Action::setLock(bool _lock){
  lock = _lock;
}

bool Action::isLocked(){
  return lock;
}

void Action::setPriority(int _priority){
  priority = _priority;
}

int Action::getPriority(){
  return priority;
}
