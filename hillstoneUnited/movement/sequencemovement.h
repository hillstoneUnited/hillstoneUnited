#ifndef SEQUENCEMOVEMENT_H
#define SEQUENCEMOVEMENT_H

#include "../util.h"
#include "movementbase.h"
#include "sequence.h"

  class SequenceMovement : public MovementBase{
    public:
      SequenceMovement(std::string _name);
      ~SequenceMovement();
      
      std::string getNextAngle(World& w);

      void setNewSequence(Sequence newSeq);
      void setNewSequence(std::string name);

    private:
      std::string name;
      int timeStamp;
      Sequence seq;
  };

#endif
