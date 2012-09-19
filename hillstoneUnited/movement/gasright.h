#ifndef GASRIGHT_H
#define GASRIGHT_H

#include "gabase.h"

  class GASRight : public GABase{
    public:
      GASRight();
      ~GASRight();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
