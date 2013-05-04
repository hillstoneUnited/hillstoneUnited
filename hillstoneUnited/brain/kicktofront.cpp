#include "kicktofront.hpp"
#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

KickToFront::KickToFront(World& w){
		// angle:count = 90:15
		//std::cout << "KickTo constructed!!" << std::endl;
    finish_flag = false;
    judgement(w);
    updateFinishFlag(w);
}

//void KickToFront::turn(World& w){
//
//  double dp_angle = target_angle - w.getABSANGLE();
//  if(dp_angle < -180){
//  		dp_angle = 360 + dp_angle;
//  }
//  if(dp_angle > 180){
//  		dp_angle = -360 + dp_angle;
//  }
//
//  int count = int( (fabs(dp_angle)*15) / 90 );
//  if(dp_angle > 0){
//  		elementList.push_back(new TicktackBase("TRIGHT_IN",count));
//  }
//  else{
//  		elementList.push_back(new TicktackBase("TLEFT_IN",count));
//  }
//}

void KickToFront::judgement(World& w){
		elementList.push_back(new SequenceMovement("LAROUND"));
		std::cout << w.getXY(0) << "," << w.getXY(1) << std::endl;
}


void KickToFront::updateFinishFlag(World& w)
{

			finish_flag = false;

}
