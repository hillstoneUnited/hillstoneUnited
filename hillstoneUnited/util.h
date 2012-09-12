#ifndef UTIL_H
#define UTIL_H

enum ActionName{
  STOP,
  FORWARD,
  SLOW_FORWARD,
  DRIBBLE,
  R_DRIBBLE,
  L_DRIBBLE,
  R_DRIBBLE_SHARP,
  L_DRIBBLE_SHARP,
  BACK,
  SLOW_BACK,
  TLEFT,
  TRIGHT,
  TLEFT_IN,
  TRIGHT_IN,
  SLEFT,
  SRIGHT,
  DUMMY,
  KICK,
  FLEFT,
  FRIGHT,
  FFORWARD,
  LAROUND,
  GA_FORWARD,
  GA_BACK,
  GA_L_DRIBBLE_SHARP,
  GA_R_DRIBBLE_SHARP,
  GA_SLEFT,
  GA_SRIGHT,
  GAWALKING,
  FFWALK,
  STANDUP,
};

/*
struct Decision{
  Action act;
  int count;
  int lock; //in Brain    -1:unlock  0:default  1:lock
            //in Walking  0:not locked  1:locked
  int priority;

  Decision(){
    act = DUMMY;
    count = 0;
    lock = 0;
    priority = 0;

  }
};
*/

enum Side{
  UNKNOWN,
  LEFT,
  RIGHT
};

enum jointID{
  hj1, hj2,
  laj1, raj1, laj2, raj2, laj3, raj3, laj4, raj4,
  llj1, rlj1, llj2, rlj2, llj3, rlj3, llj4, rlj4, llj5, rlj5, llj6, rlj6
};

enum seenID{
  g1l, g2l, g1r, g2r,
  f1l, f2l, f1r, f2r,
  bal
};

#endif
