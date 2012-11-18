#include "brain.h"

Brain::Brain(){}

Brain::~Brain(){}

void Brain::think(World& w){
    if(true){
        MovementBase* mb = new SequenceMovement("LAROUND");
        movementList.push_back(mb);
        mb = new GABase("GA_FORWARD");
        movementList.push_back(mb);
        std::cout << "LAROUND is called!" << std::endl;
        // ....
    } else if(false){
        MovementBase* mb = new TicktackBase("DRIBBLE");
        movementList.push_back(mb);
        std::cout << "DRIBBLE!" << std::endl;
    } else{
        // ....
    }
}

std::string Brain::getString(World& w){
    if(movementList.empty()){
        std::cout << "emp!!" << std::endl;
        return "hoge";
    }
    return movementList.front()->getNextAngle(w);
}

void Brain::update(World& w){
    // check fall down
    if(isFallen(w)){
        MovementBase* mb = new Standup();
        movementList.clear();
        movementList.push_back(mb);
    }
    
    if(!movementList.empty()){
        if(movementList.front()->isFinished()){
            movementList.pop_front();
        }else{
            // movement hasn't finished.
        }
    }
    
    if(movementList.empty()){
        think(w);
    }
}

bool Brain::isFallen(World &w){
    //check whether agent is fallen down
	const int limen = 10;
	double ACC_Sum[2];
	ACC_Sum[0] = w.getACC_Sum(0,limen);
	ACC_Sum[1] = w.getACC_Sum(1,limen);

  if((fabs(ACC_Sum[1]) > 9.0 * limen) && (fabs(ACC_Sum[1]) < 15 * limen)){
  	std::cout << "I'm utsubuse!" << std::endl;
    return true; //utsubuse or aomuki
  } else if((fabs(ACC_Sum[0]) > 9.0 * limen) && (fabs(ACC_Sum[0]) < 15 * limen)){
  	std::cout << "I'm yokomuki" << std::endl;
    return true; //yokomuki
  } else{
    return false;
  }
}
