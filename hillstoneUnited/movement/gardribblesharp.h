#ifndef GARDRIBBLESHARP_H
#define GARDRIBBLESHARP_H

#include "gabase.h"

  class GARDribbleSharp : public GABase{
    public:
      GARDribbleSharp();
      ~GARDribbleSharp();

      std::string getNextAngle(Action& act, World& w);
    private:
  };

#endif
