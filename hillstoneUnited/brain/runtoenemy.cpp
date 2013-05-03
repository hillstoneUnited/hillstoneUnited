#include "runtoenemy.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

RunToEnemy::RunToEnemy(World& w, int _enemy_unum){
    finish_flag = false;
    enemy_unum = _enemy_unum;
    
    for(int i=0; i<2; i++){
      enemy[i] = w.getENEMY(enemy_unum, i);
    }
    conf_enemy = w.confENEMY(enemy_unum);
    t_count = abs(15 * enemy[1] / 360);

    elementList.push_back(new SequenceMovement("LAROUND"));
}

void RunToEnemy::judgement(World& w){
    for(int i=0; i<2; i++){
      enemy[i] = w.getENEMY(enemy_unum, i);
    }
    conf_enemy = w.confENEMY(enemy_unum);

    t_count = abs(15 * enemy[1] / 360);
    if(t_count == 0){
      t_count = 1;
    }

    if(conf_enemy == 300){
      elementList.push_back(new TicktackBase("TLEFT", 2));
      elementList.push_back(new SequenceMovement("LAROUND"));
    }
    else{
      if(enemy[0] > 6){
	if(enemy[1] > 15){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(enemy[1] > -15){
    elementList.push_back(new TicktackBase("FORWARD", 5));
	  elementList.push_back(new GABase("GA_FORWARD", 200));
	}
	else{
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
      }
      else if(enemy[0] > 2){
	if(enemy[1] > 10){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(enemy[1] > -10){
    elementList.push_back(new TicktackBase("FORWARD", 5));
	  elementList.push_back(new GABase("GA_FORWARD", 100));
	}
	else{
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
      }
      else{
	if(enemy[1] > 3){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(enemy[1] > -3){
    elementList.push_back(new TicktackBase("FORWARD", 5));
	  elementList.push_back(new GABase("GA_FORWARD", 100));
	}
	else{
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
      }
    }
    
}

void RunToEnemy::updateFinishFlag(World& w)
{
  if(enemy[0] < 0.8 && conf_enemy == 0){
    finish_flag = true;
  }
  else{
    finish_flag = false;
  }
}
