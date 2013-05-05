#include "kick.hpp"


Kick::Kick(){
  ts = 0;
  state = ACT;
  std::cout << "kick is started" << std::endl;
  finish_flag = false;
}

Kick::~Kick(){
}


std::string Kick::getNextAngle(World& w){
  resetAngleMap();

  

  switch(state){
  case ACT:
    set(w, rlj2,  7.0, 0.2);
    set(w, llj2,  7.0, 0.2);
    set(w, rlj3,  0.0, 0.11);
    set(w, llj3,  0.0, 0.11);
    set(w, rlj4, -0.77, 0.33);
    set(w, llj4, -0.77, 0.33);
    set(w, rlj5,  3.45, 0.35);
    set(w, llj5,  3.45, 0.35);
    set(w, rlj6,  -7.0, 0.2);
    set(w, llj6,  -7.0, 0.2);

    if( ts > 20){
      state = SETTING;
      ts = 0;
    }
    ts++;
    break;

  case SETTING:
    set(w, llj2, -10.0, 0.2);
    set(w, llj6,  10.0, 0.2);
    //set(w, rlj3,  0.5, 0.2);
    //set(w, rlj4, -2.0, 0.2);
    set(w, llj4, -61.07, 0.19);
    set(w, llj5,  36.16, 0.42);
    set(w, rlj2,  10.0, 0.2);
    set(w, rlj6, -10.0, 0.2);

    if( ts > 20 ){    
      state = FIRE;
      ts = 0;
    }
    ts++;
    break;

  case FIRE:
    set(w, llj3,  66.61, 11.41);
    set(w, llj4, -0.46, 8.67);
    set(w, llj5,  29.33, 9.32);
    set(w, rlj3,  -14.48, 14.48);
    set(w, rlj5,  11.94, 12.14);
    //set(w, llj4, -0.77, 0.33);
      
    if(ts > 5){
      state = ACT;
      finish_flag = true;
    }
    ts++;
    break;

  default:
    break;
  }
  return angleToString();
}
