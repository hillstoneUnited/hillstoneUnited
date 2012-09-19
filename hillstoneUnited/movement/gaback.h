#ifndef GABACK_H
#define GABACK_H

#include "gabase.h"

  class GABack : public GABase{
    public:
      GABack();
      ~GABack();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
