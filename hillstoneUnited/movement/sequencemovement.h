#ifndef SEQUENCEMOVEMENT_H
#define SEQUENCEMOVEMENT_H

#include "../util.h"
#include "movementbase.h"
#include "sequence.h"

  class SequenceMovement : public MovementBase{
    public:
      SequenceMovement();
      ~SequenceMovement();

      void renew(int& ts);
      
      std::string getNextAngle(Action& act, World& w, int& ts);

      void setNewSequence(Sequence newSeq);
      void setNewSequence(std::string name);

    private:
      int timeStamp;
      Sequence seq;
  };

#endif
