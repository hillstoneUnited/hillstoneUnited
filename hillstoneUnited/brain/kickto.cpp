#include "kickto.hpp"
#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

KickTo::KickTo(World& w ,double _target_angle){
		// angle:count = 90:15
		//std::cout << "KickTo constructed!!" << std::endl;
    finish_flag = false;

    is_kicked = false;
    target_angle = _target_angle;
    judgement(w);
    updateFinishFlag(w);
}

void KickTo::turn(World& w){

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

	elementList.push_back(new SequenceMovement("LAROUND"));

	//kick
	if( fabs( fabs( target_angle )-fabs( w.getABSANGLE() ) ) < 10){
		//modify rellation(agent-ball) angle
		double ballangle = w.getBAL(1);
		//count:angle = 6:90
		int count = int(6*fabs(ballangle)/90);
		if(count<3){
			count+=1;
		}

		if(ballangle !=0){

			if(ballangle>0 && count>1){
				elementList.push_back(new SequenceMovement("DUMMY"));
				elementList.push_back(new TicktackBase("TLEFT",count));
			}
			else if(count>1){
				elementList.push_back(new SequenceMovement("DUMMY"));
				elementList.push_back(new TicktackBase("TRIGHT",count));
			}
        }


		if(true){
			//std::cout << "KickTo::kick!!" << std::endl;
			elementList.push_back(new SequenceMovement("DUMMY"));
			elementList.push_back(new TicktackBase("FORWARD",2));
			elementList.push_back(new GABase("GA_FORWARD",100));
			is_kicked = true;

		}
	}
	else{
		turn(w);
    }
}


void KickTo::updateFinishFlag(World& w)
{
		if(is_kicked){
			finish_flag = true;
		}
		else{
			finish_flag = false;
            judgement(w);
		}
}
