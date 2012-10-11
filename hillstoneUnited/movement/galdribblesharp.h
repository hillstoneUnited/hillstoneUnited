#ifndef GALDRIBBLESHARP_H
#define GALDRIBBLESHARP_H

#include "gabase.h"

  class GALDribbleSharp : public GABase{
    public:
      GALDribbleSharp();
      ~GALDribbleSharp();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
