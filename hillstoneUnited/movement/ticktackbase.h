//
//  ticktackbase.h
//  
//
//  Created by Yoshihiro Nagano on 2012/09/12.
//
//

#ifndef TICKTACKBASE_H
#define TICKTACKBASE_H

#include <math.h>

#include "../util.h"
#include "movementbase.h"

  class TicktackBase : public MovementBase{
    public:
      TicktackBase();
      virtual ~TicktackBase(){};

      void renew(Action& act);
      void setAngle(Action& act, World& w);

      virtual std::string getNextAngle(Action act, World& w){};


    protected:
      double t;
      double m_rlj1, m_rlj2, m_rlj3, m_rlj4, m_rlj5, m_rlj6;
      double m_llj1, m_llj2, m_llj3, m_llj4, m_llj5, m_llj6;
      double lj26;
      double m_hj1, m_hj2, headSpeed;
      double L, S, cycle;

      // Walking parameter
      double wX, wY, r;
      double Gain, Threshold;
      int H, dummy_H, max_H;
      bool drive, start;

      int current;
  };
#endif
