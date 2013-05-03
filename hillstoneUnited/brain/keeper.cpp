#include "keeper.hpp"
//#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

Keeper::Keeper(World& w){
    finish_flag = false;
    updateFinishFlag(w);
}

void Keeper::judgement(World& w){
		double dis = w.getBAL(0);
		double angle = w.getBAL(1);
		std::cout << "BAL" << dis << ","<< angle << std::endl;
		if(dis < 1.5 && dis > 0.8){
				elementList.push_back( new TicktackBase("SLEFT",10));
				elementList.push_back( new TicktackBase("SLEFT",10));
		}
		else if(dis <= 0.8){
				std::cout << "patari..." << std::endl;
			  if(angle>0){
			  		elementList.push_back(new SequenceMovement("FLEFT"));
			  }
			  else{
			  		elementList.push_back(new SequenceMovement("FRIGHT"));
			  }
		}
		else{
				elementList.push_back(new SequenceMovement("DUMMY"));
		}

}


void Keeper::updateFinishFlag(World& w)
{
		finish_flag = false;
}
