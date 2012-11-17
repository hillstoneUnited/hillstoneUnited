#ifndef GABASE_H
#define GABASE_H

#include <math.h>

#include "../util.h"
#include "movementbase.h"

  class GABase : public MovementBase{
    public:
      GABase(){};
      ~GABase(){};

      void renew(int& ts);
      void updateAngle();
      void setAngle(World& w);

      virtual std::string getNextAngle(World& w){};


    protected:
      /** Parameters **/
      double t;
      double ga_param[17][3];
      double ga_W;
      double ga_I;
      double ga_Gain;

      /** Head **/
      double m_hj1, m_hj2;
      /** Right Arms **/
      double m_raj1, m_raj2, m_raj3, m_raj4;
      /** Left Arms **/
      double m_laj1, m_laj2, m_laj3, m_laj4;
      /** Right Legs **/
      double m_rlj1, m_rlj2, m_rlj3, m_rlj4, m_rlj5, m_rlj6;
      /** Left Legs **/
      double m_llj1, m_llj2, m_llj3, m_llj4, m_llj5, m_llj6;
  };
#endif
