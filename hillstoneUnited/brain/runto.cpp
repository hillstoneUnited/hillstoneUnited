#include "runto.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

RunTo::RunTo(World& w, double _point[]){
    finish_flag = false;
    point[0] = _point[0];
    point[1] = _point[1];
    
    x = w.getXY(0);
    y = w.getXY(1);
    conf_XY = w.confXY();
    dist = sqrt(((point[0] - x)*(point[0] - x))
		+((point[1] - y)*(point[1] - y)));
    my_angle = w.getABSANGLE();
    u = ((point[0] - x) * cos(-my_angle))
      + ((point[1] - y) * -sin(-my_angle));
    v = ((point[0] - x) * sin(-my_angle))
      + ((point[1] - y) *  cos(-my_angle));
    angle = atan(v/u) * 180/M_PI;
    if(u < 0 && v >= 0){ angle +=  180;}
    else if(u < 0 && v < 0){ angle += -180;}

    t_count = abs(15 * angle / 360);

    elementList.push_back(new SequenceMovement("LAROUND"));
    updateFinishFlag(w);
}

void RunTo::judgement(World& w){
    x = w.getXY(0);
    y = w.getXY(1);
    conf_XY = w.confXY();
    dist = sqrt(((point[0] - x)*(point[0] - x))
		 +((point[1] - y)*(point[1] - y)));
    my_angle = w.getABSANGLE() * M_PI/180;
    u = ((point[0] - x) * cos(-my_angle))
      + ((point[1] - y) * -sin(-my_angle));
    v = ((point[0] - x) * sin(-my_angle))
      + ((point[1] - y) *  cos(-my_angle));
    angle = atan(v/u) * 180/M_PI;
    if(u < 0 && v >= 0){ angle +=  180;}
    else if(u < 0 && v < 0){ angle += -180;}

    t_count = abs(15 * angle / 360);
    if(t_count == 0){
      t_count = 1;
    }

    if(conf_XY == 300){
      elementList.push_back(new TicktackBase("TLEFT", 2));
      elementList.push_back(new SequenceMovement("LAROUND"));
    }
    else{
      if(dist > 2.0){
	if(angle > 20){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(angle < -20){
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
	else{
	  elementList.push_back(new SequenceMovement("DUMMY"));
	  elementList.push_back(new TicktackBase("FORWARD", 10));
	  elementList.push_back(new GABase("GA_FORWARD", 10));
	}
      }
      else{
	if(angle > 10){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(angle < -10){
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
	else{
	  elementList.push_back(new TicktackBase("FORWARD", 5));
	  elementList.push_back(new TicktackBase("DRIBBLE", 10));
	}
      }
    }

}

void RunTo::updateFinishFlag(World& w)
{
    if(abs(point[0] - w.getXY(0)) < 0.8 &&
       abs(point[1] - w.getXY(1)) < 0.8)
    {
      finish_flag = true;
    } else {
      finish_flag = false;
      judgement(w);
    }
}
