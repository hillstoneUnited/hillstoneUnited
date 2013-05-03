#include "keeper.hpp"
//#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

Keeper::Keeper(World& w){
    finish_flag = false;
    updateFinishFlag(w);
}

void KickTo::judgement(World& w){
		double dis = w.getBAL(0);
		double angle = w.getBAL(1);
		std::cout << "BAL" << dis << ","<< angle << std::endl;

		elementList.push_back(new SequenceMovement("DUMMY"));
}


void KickTo::updateFinishFlag(World& w)
{
		finish_flag = false;
}
