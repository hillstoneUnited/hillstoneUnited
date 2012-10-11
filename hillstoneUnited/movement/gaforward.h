#ifndef GAFORWARD_H
#define GAFORWARD_H

#include "gabase.h"

  class GAForward : public GABase{
    public:
      GAForward();
      ~GAForward();

      std::string getNextAngle(Action& act, World& w, int& ts);
    private:
  };

#endif
