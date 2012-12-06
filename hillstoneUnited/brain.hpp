#ifndef BRAIN_H
#define BRAIN_H

#include "movement/movementbase.hpp"
#include "movement/sequencemovement.hpp"
#include "movement/ticktackbase.hpp"
#include "movement/gabase.hpp"
#include "movement/standup.hpp"

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
