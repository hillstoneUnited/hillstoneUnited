#include "kicktofront.hpp"
#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

KickToFront::KickToFront(World& w){
		// angle:count = 90:15
		//std::cout << "KickTo constructed!!" << std::endl;
    finish_flag = false;
    isKicked = false;
    judgement(w);
    updateFinishFlag(w);

    modanglecount = 0;
    not_seeBALLcount = 0;
    modmyposcount = 0;
}


void KickToFront::judgement(World& w){
		//std::cout << "mypos" << w.getXY(0) << "," << w.getXY(1) << std::endl;
		//std::cout << "ballpos" << w.getBXY(0) << "," << w.getBXY(1) << std::endl;


		if(w.confBAL()>100 || w.getBXY(0)==0){
				//std::cout << "LAROUND" << std::endl;
				//elementList.push_back(new SequenceMovement("READY"));
				elementList.push_back(new SequenceMovement("LAROUND"));
				not_seeBALLcount +=1;
				if(not_seeBALLcount>3){
					elementList.push_back(new TicktackBase("TRIGHT",3));
				}
				return;
		}
		if( w.getXY(0) < w.getBXY(0) && fabs( w.getXY(1)-w.getBXY(1) ) <2 && w.getXY(0)+3 > w.getBXY(0)){
				not_seeBALLcount = 0;
				modmyposcount = 0;
				modanglecount+=1;
				//modify rellation(agent-ball) angle
				double ballangle = w.getBAL(1);
				//count:angle = 6:90
				int count = int(8*fabs(ballangle)/90);
				int dcount = int(w.getBAL(0)*6);
				int dcount_limit = 30;
				if(w.getBAL(0)<3){
					dcount_limit = 7;
				}
				if(dcount < 2){
					dcount=1;
				}
				else if(dcount > dcount_limit){
					dcount = dcount_limit;
				}


				//std::cout << "mod angle" << count << std::endl;
					if(ballangle>0){
						//elementList.push_back(new SequenceMovement("READY"));
						elementList.push_back(new TicktackBase("TLEFT",count));
					}
					else{
						//elementList.push_back(new SequenceMovement("READY"));
						elementList.push_back(new TicktackBase("TRIGHT",count));
					}

				if(modanglecount > 5){
					//std::cout << "kick" <<" dcount" <<dcount << std::endl;
					modanglecount = 0;
					elementList.push_back(new SequenceMovement("DUMMY"));
					elementList.push_back(new TicktackBase("FORWARD",dcount));
					isKicked = true;
				}
				if(fabs(ballangle)<5 && w.getBAL(0)<0.8){
					//std::cout << "cho kick" <<ballangle  << "dcount"<< dcount<<  std::endl;
					modanglecount = 0;
					elementList.push_back(new SequenceMovement("DUMMY"));
					elementList.push_back(new TicktackBase("FORWARD",dcount));
					isKicked = true;
				}
		}
		else{
				modmyposcount += 1;
				if(modmyposcount > 10){
						elementList.push_back(new TicktackBase("FORWARD",5));
				}
				//std::cout << "modify position" << std::endl;
				//ball no kage ni irutoki
				if(w.getXY(0) > w.getBXY(0) && fabs( w.getXY(1)-w.getBXY(1) ) <0.1){
						double tpos[2];
						tpos[0] = w.getBXY(0)+0.3;
						if(w.getXY(1)>w.getBXY(1)){
								tpos[1] = w.getBXY(1)+0.5;
						}
						else{
								tpos[1] = w.getBXY(1)-0.5;
						}
						//std::cout << "hosei" << std::endl;
						elementList.push_back(new RunToSlowly(w,tpos));
				}
				double kpos[2] = {w.getBXY(0)-0.8,w.getBXY(1)};
				elementList.push_back(new RunToSlowly(w,kpos));
		}
}


void KickToFront::updateFinishFlag(World& w)
{
		if(isKicked and w.getBAL(0)>3){
			finish_flag = true;
		}
		else{
			judgement(w);
		}

}
