#ifndef BRAIN_H
#define BRAIN_H

#include "movement/movementbase.h"
#include "movement/sequencemovement.h"
#include "movement/ticktackbase.h"
#include "movement/gabase.h"
#include "movement/standup.h"

class Brain {
  public:
    Brain();
    ~Brain();

    void think(World& w);

    std::string getString(World& w);
    
    void checkResponse(World& w);
    void updateList();
    
    bool isFallen(World& w);
    bool allListEmpty();

  private:
    std::deque<MovementBase*> movementList;
    std::deque<MovementBase*> responseList;
};

#endif
