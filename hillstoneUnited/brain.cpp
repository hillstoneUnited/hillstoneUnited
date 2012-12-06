#include "brain.hpp"

Brain::Brain(){}

Brain::~Brain(){}

void Brain::think(World& w){
    if(true){
        MovementBase* mb = new SequenceMovement("LAROUND");
        movementList.push_back(mb);
        mb = new GABase("GA_FORWARD");
        movementList.push_back(mb);
        // ....
    } else if(false){
        MovementBase* mb = new TicktackBase("DRIBBLE");
        movementList.push_back(mb);
    } else{
        // ....
    }
}

std::string Brain::getString(World& w){
    if(!responseList.empty()){
        return responseList.front()->getNextAngle(w);
    }else{
        if(movementList.empty()){
            std::cout << "emp!!" << std::endl;
            return "hoge";
        }else{
            return movementList.front()->getNextAngle(w);
        }
    }
}

void Brain::checkResponse(World &w){
    if(isFallen(w)){
        if(responseList.empty()){
            MovementBase* mb = new Standup();
            movementList.clear();
            responseList.push_back(mb);
            std::cout << "Standup pushed!" << std::endl;
        }else{
            // continue the response movement
        }
    }else{
        // is not fallen
    }
}

void Brain::updateList(){
    if(!responseList.empty() && !movementList.empty()){
        std::cout << "Warning: Both movementList and responseList are filled." << std::endl;
        std::cout << "You have to fix the code." << std::endl;
    }
    
    if(!responseList.empty()){
        if(responseList.front()->isFinished()){
            responseList.pop_front();
        }else{
            // continue
        }
    }else{
        if(!movementList.empty()){
            if(movementList.front()->isFinished()){
                movementList.pop_front();
            }else{
                // continue
            }
        }else{
            // movementList is empty. This agent will think()
            std::cout << "all lists are empty" << std::endl;
        }
    }
}

bool Brain::isFallen(World &w){
    //check whether agent is fallen down
	const int limen = 10;
	double ACC_Sum[2];
	ACC_Sum[0] = w.getACC_Sum(0,limen);
	ACC_Sum[1] = w.getACC_Sum(1,limen);

  if((fabs(ACC_Sum[1]) > 9.0 * limen) && (fabs(ACC_Sum[1]) < 15 * limen)){
    return true; //utsubuse or aomuki
  } else if((fabs(ACC_Sum[0]) > 9.0 * limen) && (fabs(ACC_Sum[0]) < 15 * limen)){
    return true; //yokomuki
  } else{
    return false;
  }
}

bool Brain::allListEmpty(){
    return (responseList.empty() && movementList.empty());
}
