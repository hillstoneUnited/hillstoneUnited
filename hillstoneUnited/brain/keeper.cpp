#include "keeper.hpp"
//#include <math.h>

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

Keeper::Keeper(World& w, double _initpos[]){
    finish_flag = false;
    beam_flag = false;
    updateFinishFlag(w);
    null_anglecount = 0;

    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
    initpos[2] = _initpos[2];
}

void Keeper::restore_position(World& w){
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
				if(0-angle<0){
						elementList.push_back(new TicktackBase("TRIGHT",count));
				}
				else{
						elementList.push_back(new TicktackBase("TLEFT",count));
				}
		}
}

void Keeper::judgement(World& w){
      judge_stand = true;
      restore_position(w);
      bal[0] = w.getBAL(0);
      bal[1] = w.getBAL(1);
      conf_bal = w.confBAL();
      ballpos[0] = w.getBXY(0);
      ballpos[1] = w.getBXY(1);
      x = w.getXY(0);
      y = w.getXY(1);
      conf_XY = w.confXY();
      
      judgeStandup(w);
      
      if(conf_bal >= 300 || conf_ballpos >= 300){
	elementList.push_back(new SequenceMovement("DUMMY"));
	elementList.push_back(new SequenceMovement("LAROUND"));
      }
      else{		 
	if((bal[0] > 10) && ((fabs(x + 13.5) > 4 || fabs(y - 0) > 4))){
	  double runto_pos[2] = {-13.5,0};
	  elementList.push_back(new RunTo(w,runto_pos));
	}
	else if(fabs(ballpos[1]) - 0.5 < w.getGoalLength()/2){
	  if(bal[0] < 5.0 && bal[0] > 1.5){
	    if(bal[1] > 0){
	      elementList.push_back( new TicktackBase("SLEFT",2));
	    }
	    else{
	      elementList.push_back( new TicktackBase("SRIGHT",2));
	    }
	  }
	  else if(bal[0] <= 1.5){	    
	    if(bal[1] > 20){
	      elementList.push_back(new TicktackBase("SLEFT",2));
	    }
	    else if(bal[1] > -20){
	      elementList.push_back(new SequenceMovement("LSPREAD"));
	      judge_stand = false;
	    }
	    else{
	      elementList.push_back(new TicktackBase("SRIGHT",2));
	    }
	  }
	  else{
	    elementList.push_back(new SequenceMovement("DUMMY"));
	  }
	}

	else{
	  if(bal[0] < 5.0 && bal[0] > 1.5){
	    if(bal[1] > 40){
	      elementList.push_back( new TicktackBase("SLEFT",2));
	    }
	    else if(bal[1] < -40){
	      elementList.push_back( new TicktackBase("SRIGHT",2));
	    }
	    else{
	      elementList.push_back(new SequenceMovement("DUMMY"));
	    }
	  }
	  else if(bal[0] <= 1.5){
	    
	    if(bal[1] > 40){
	      elementList.push_back(new TicktackBase("SLEFT",2));
	    }
	    else if(bal[1] > -40){
	      elementList.push_back(new SequenceMovement("LSPREAD"));
	      judge_stand = false;
	    }
	    else{
	      elementList.push_back(new TicktackBase("SRIGHT",2));
	    }
	  }
	  else{
	    elementList.push_back(new SequenceMovement("DUMMY"));
	  }
	}
      }
      
      /*
		if(dis < 1.5 && dis > 0.8){
				elementList.push_back( new TicktackBase("SLEFT",2));
				elementList.push_back( new TicktackBase("SRIGHT",2));
		}
		else if((dis <= 0.8 && dis != 0) || w.getXY(0)>w.getBXY(0)){
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
      */
}


void Keeper::updateFinishFlag(World& w)
{
        finish_flag = false;
        judgement(w);
}


std::string Keeper::getNextAngle(World& w) {
    std::stringstream ss;
    if((w.getPlaymode()=="BeforeKickOff" ||
       w.getPlaymode()=="Goal_Left" ||
       w.getPlaymode()=="Goal_Right") && w.getUnum()>0){
        beam_flag = true;
        ss << "(beam " << initpos[0] << " "
                << initpos[1] << " " << initpos[2]
                << ")";
        // std::cout << ss.str() << std::endl;
    }

    if (w.isFalling())
    {
        if (pushStand)
        {
            /* code */
        } else if(judge_stand == true) {
            elementList.clear();
            elementList.push_front(new Standup());
            pushStand = true;
        }
    } else {
        pushStand = false;
    }

    rtn = elementList.front()->getNextAngle(w);
    if(beam_flag){
        rtn += ss.str();
        beam_flag = false;
    }
    if (elementList.front()->isFinished())
    {
        ElementBase* tmp = elementList.front();
        delete tmp;
        elementList.pop_front();
    }
    if (finishAllChild(w))
    {
        updateFinishFlag(w);
    }
    return rtn;
}
