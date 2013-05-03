#include "keeper.hpp"
//#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

Keeper::Keeper(World& w){
    finish_flag = false;
    updateFinishFlag(w);
    null_anglecount = 0;
}

void Keeper::restore_position(World& w){
		std::cout << w.getABSANGLE() << std::endl;
		if( w.getABSANGLE()==0 ){
				null_anglecount+=1;
		}
		else{
				null_anglecount=0;
		}

		if(null_anglecount > 10){
				elementList.push_back(new TicktackBase("TLEFT",4));
				elementList.push_back(new SequenceMovement("LAROUND"));
		}
		else if( fabs(w.getABSANGLE() )>15 ){
				double angle = w.getABSANGLE();
				int count = int( 6*fabs(angle)/90 );
				std::cout <<"count" << count << std::endl;
				if(0-angle<0){
						elementList.push_back(new TicktackBase("TRIGHT",count));
				}
				else{
						elementList.push_back(new TicktackBase("TLEFT",count));
				}
		}
}

void Keeper::judgement(World& w){
		restore_position(w);
		double dis = w.getBAL(0);
		double angle = w.getBAL(1);
		std::cout << "BAL" << dis << ","<< angle << std::endl;
		if(dis < 1.5 && dis > 0.8){
				elementList.push_back( new TicktackBase("SLEFT",2));
				elementList.push_back( new TicktackBase("SRIGHT",2));
		}
		else if(dis <= 0.8 && dis != 0){
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
