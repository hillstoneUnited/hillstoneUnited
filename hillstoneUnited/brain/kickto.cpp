#include "kickto.hpp"
#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

KickTo::KickTo(World& w ,double _target_angle){
		// angle:count = 90:15
    finish_flag = false;

    is_kicked = false;
    target_angle = _target_angle;
    updateFinishFlag(w);
}

void KickTo::turn(World& w){
	std::cout << "KickTo::turning!" << std::endl;
  double dp_angle = target_angle - w.getABSANGLE();
  if(dp_angle < -180){
  		dp_angle = 360 + dp_angle;
  }
  if(dp_angle > 180){
  		dp_angle = -360 + dp_angle;
  }

  int count = int( (fabs(dp_angle)*15) / 90 );
  if(dp_angle > 0){
  		elementList.push_back(new TicktackBase("TRIGHT_IN",count));
  }
  else{
  		elementList.push_back(new TicktackBase("TLEFT_IN",count));
  }
}

void KickTo::judgement(World& w){
		std::cout << "judgement" << std::endl;
		elementList.push_back(new SequenceMovement("LAROUND"));

		//kick
		if( fabs( fabs( target_angle )-fabs( w.getABSANGLE() ) ) < 10 && !is_kicked){
				std::cout << "KickTo::kick!!" << std::endl;
				elementList.push_back(new SequenceMovement("DUMMY"));
				elementList.push_back(new TicktackBase("FORWARD",5));
				elementList.push_back(new GABase("GA_FORWARD",100));
				//is_kicked = true;
		}
		else{
				std::cout << "modify my angle" <<std::endl;
				turn(w);
		}
}


void KickTo::updateFinishFlag(World& w)
{
	std::cout << "updateFinishFlag" << std::endl;
		if(is_kicked){
			finish_flag = true;
		}
		else{
			finish_flag = false;
		}
}
