#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "util.h"

/*
 */
class Action{
 public:
  Action();
  ~Action();

  void setName(ActionName _name);
  ActionName getName();

  void setCount(int _count);
  int getCount();

  void setLock(bool _lock);
  bool isLocked();

  void setPriority(int _priority);
  int getPriority();

 private:
  ActionName name;
  int count;
  bool lock;
  int priority;

};

#endif
