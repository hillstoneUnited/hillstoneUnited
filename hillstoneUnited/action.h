#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "util.h"

/*
 */
class Action{
 public:
  Action(ActionName _name=DUMMY, int _count=30);
  ~Action();

  void setName(ActionName _name);
  ActionName getName();

  void setCount(int _count);
  int getCount();

  void setFinished(bool _finished);
  bool isFinished();

  void setLock(bool _lock);
  bool isLocked();

  void setPriority(int _priority);
  int getPriority();

 private:
  ActionName name;
  int count;
  bool finished;
  bool lock;
  int priority;

};

#endif
