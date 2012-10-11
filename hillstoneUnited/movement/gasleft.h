#ifndef GASLEFT_H
#define GASLEFT_H

#include "gabase.h"

  class GASLeft : public GABase{
    public:
      GASLeft();
      ~GASLeft();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
