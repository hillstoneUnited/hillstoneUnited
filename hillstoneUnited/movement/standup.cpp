#include "standup.hpp"

int Standup::ts = 0;

Standup::Standup(){
}

Standup::~Standup(){}


std::string Standup::getNextAngle(World& w){

  resetAngleMap();

  const int TH = 40;
  const int COUNTTH = 10;
  double ACC_Sum[2]; // average of ACC_Sum
  ACC_Sum[0] = w.getACC_Sum(0, COUNTTH) / COUNTTH;
  ACC_Sum[1] = w.getACC_Sum(1, COUNTTH) / COUNTTH;
  static int actiontype = -1; // -1:reset  0:standup 1:reverse standup
  enum behaviorState{
    READY,
    STAND0,
    STAND1,
    STAND2,
    REVERSE0,
    REVERSE1,
    REVERSE2,
    REVERSE3,
    REVERSE4,
    WAIT,
    END
  };
  static behaviorState state;

  if(actiontype == -1){
    ts = -1;
    state = READY;

    if(ACC_Sum[1] > 9.0 && ACC_Sum[1] < 15){
      // aomuki ?
      std::cout << "standupAction : I'm aomuki" << std::endl;
      actiontype = 1;
    }else if(ACC_Sum[1] < -9.0 && ACC_Sum[1] > -15){
      std::cout << "standupAction : I'm utsubuse" << std::endl;
      actiontype = 0;
    }else if(fabs(ACC_Sum[0]) > 9.0 && fabs(ACC_Sum[0]) < 15){
      // yokomuki
      std::cout << "standupAction : I'm yokomuki" << std::endl;
      actiontype = 1;
    }else{
      std::cout << "standupAction : unknown falling?" << std::endl;
      std::cout << "I'm not falling?" << std::endl;
      actiontype = -1;
      state = END;
    }
  }

  switch(state){
  case READY:
    if(actiontype == 0){
      ts = -1;
      state = STAND0;
    }else if(actiontype == 1){
      ts = -1;
      state = REVERSE0;
    }else{
      std::cout << "standupAction : READY : not falling?" << std::endl;
      ts = -1; // not to stop movement
      state = END;
    }
    break;

  case STAND0:
    set(w, hj1, 0.0);
    set(w, hj2, 0.0);
    set(w, raj1,  3.07, 0.15);
    set(w, laj1,  3.07, 0.15);
    set(w, raj2, -29.02, 0.19);
    set(w, laj2,  29.02, 0.19);
    set(w, raj3,  85.71, 0.23);
    set(w, laj3, -85.71, 0.23);
    set(w, raj4,  78.39, 0.13);
    set(w, laj4, -78.39, 0.13);
    set(w, rlj1, -85.12, 0.09);
    set(w, llj1, -85.12, 0.09);
    set(w, rlj2,  2.9, 0.26);
    set(w, llj2, -2.9, 0.26);
    set(w, rlj3,  100.0, 0.13);
    set(w, llj3,  100.0, 0.13);
    set(w, rlj4, -115.93, 0.21);
    set(w, llj4, -115.93, 0.21);
    set(w, rlj5,  75.0, 0.02);
    set(w, llj5,  75.0, 0.02);
    set(w, rlj6,  13.04, 0.24);
    set(w, llj6,  -13.04, 0.24);

    if( ts > TH * 0.5){
      ts = -1;
      state = STAND1;
      break;
    }
    break;

  case STAND1:
    set(w, raj1, -38.73, 0.17);
    set(w, laj1, -38.73, 0.17);
    set(w, raj2,  0.39, 0.11);
    set(w, laj2, -0.39, 0.11);
    set(w, raj4,  0.73, 0.19);
    set(w, laj4, -0.73, 0.19);
    set(w, rlj5, -6.44, 0.06);
    set(w, llj5, -6.44, 0.06);

    if( ts > TH * 0.34){    
      ts = -1;
      state = STAND2;
      break;
    }
    break;

  case STAND2:
    set(w, raj1, -100.0, 0.03);
    set(w, laj1, -100.0, 0.03);
    set(w, raj2,  0.0, 0.05);
    set(w, laj2,  0.0, 0.05);
    set(w, raj3,  90.0, 0.08);
    set(w, laj3, -90.0, 0.08);
    set(w, raj4,  90.0, 0.03);
    set(w, laj4, -90.0, 0.03);
    set(w, rlj1, 0.0, 0.01);
    set(w, llj1, 0.0, 0.01);
    set(w, rlj3, 0.0, 0.01);
    set(w, llj3, 0.0, 0.01);
    set(w, rlj4, 0.0, 0.01);
    set(w, llj4, 0.0, 0.01);
      
    if(ts > TH*2.2){
      ts = -1;
      state = WAIT;
      break;
    }
    break;

  case REVERSE0:
    set(w, hj1, 0.0);
    set(w, hj2, 0.0);
    set(w, raj1,  0.0);
    set(w, laj1,  0.0);
    set(w, raj2, -90.0, 0.1);
    set(w, laj2,  90.0, 0.1);
    set(w, raj3,  0.0);
    set(w, laj3,  0.0);
    set(w, raj4,  0.0);
    set(w, laj4,  0.0);
    set(w, rlj1, 0.0);
    set(w, llj1, 0.0);
    set(w, rlj2, 0.0);
    set(w, llj2, 0.0);
    set(w, rlj3, 0.0);
    set(w, llj3, 0.0);
    set(w, rlj4, 0.0);
    set(w, llj4, 0.0);
    set(w, rlj5, 0.0);
    set(w, llj5, 0.0);
    set(w, rlj6, 0.0);
    set(w, llj6, 0.0);

    if(ts > TH){
      ts = -1;
      state = REVERSE1;
      break;
    }
    break;

  case REVERSE1:
    set(w, raj1, -119.24, 0.21);
    set(w, laj1, -119.24, 0.21);
    set(w, raj2, -0.55, 0.14);
    set(w, laj2,  0.55, 0.14);
    set(w, raj3, -89.75, 0.21);
    set(w, laj3,  89.75, 0.21);
    set(w, raj4,  44.97, 0.15);
    set(w, laj4, -44.97, 0.15);
    set(w, rlj5,  74.62, 0.14);
    set(w, llj5,  74.62, 0.14);

    if( ts > TH * 0.51){
      ts = -1;
      state = REVERSE2;
      break;
    }
    break;

  case REVERSE2:
    set(w, rlj1, -89.44, 0.23);
    set(w, llj1, -89.44, 0.23);
    set(w, rlj3,  100.88, 0.16);
    set(w, llj3,  100.88, 0.16);
    set(w, rlj4, -129.79, 0.23);
    set(w, llj4, -129.79, 0.23);
 
    if( ts > TH * 0.28){
      ts = -1;
      state = REVERSE3;
      break;
    }
    break;

  case REVERSE3:
    set(w, raj1, -45.12, 0.21);
    set(w, laj1, -45.12, 0.21);
    set(w, raj3, -0.74, 0.14);
    set(w, laj3,  0.74, 0.14);
    set(w, raj4,  0.24, 0.18);
    set(w, laj4, -0.24, 0.18);
    set(w, rlj4, -90.43, 0.12);
    set(w, llj4, -90.43, 0.12);
    set(w, rlj5, -44.38, 0.11);
    set(w, llj5, -44.38, 0.11);

    if(ts > TH * 0.16){   
      ts = -1;
      state = REVERSE4;
      break;
    }
    break;

  case REVERSE4:
    set(w, raj1, -100.0, 0.19);
    set(w, laj1, -100.0, 0.19);
    set(w, raj2,  0.0, 0.18);
    set(w, laj2,  0.0, 0.18);
    set(w, raj3,  90.0, 0.17);
    set(w, laj3, -90.0, 0.17);
    set(w, raj4,  90.0, 0.15);
    set(w, laj4, -90.0, 0.15);
    set(w, rlj1, 0.0, 0.01);
    set(w, llj1, 0.0, 0.01);
    set(w, rlj3, 0.0, 0.06);
    set(w, llj3, 0.0, 0.06);
    set(w, rlj4, 0.0, 0.03);
    set(w, llj4, 0.0, 0.03);
    set(w, rlj5, 0.0, 0.07);
    set(w, llj5, 0.0, 0.07);

    if(ts > TH*2){
      ts = -1;
      state = WAIT;
      break;
    }
    break;

  case WAIT:
    // Head
    set(w, hj1, 0.0);
    set(w, hj2, 0.0);
    // Arms
    set(w, raj1, -100.0);
    set(w, laj1, -100.0);
    set(w, raj2,  0.0);
    set(w, laj2,  0.0);
    set(w, raj3,  90.0);
    set(w, laj3, -90.0);
    set(w, raj4,  90.0);
    set(w, laj4, -90.0);
    // Legs
    set(w, rlj1, 0.0);
    set(w, llj1, 0.0);
    set(w, rlj2, 0.0);
    set(w, llj2, 0.0);
    set(w, rlj3, 0.0);
    set(w, llj3, 0.0);
    set(w, rlj4, 0.0);
    set(w, llj4, 0.0);
    set(w, rlj5, 0.0);
    set(w, llj5, 0.0);
    set(w, rlj6, 0.0);
    set(w, llj6, 0.0);

    if(ts > 40){
      //if (tes > 1){
      state = END;
      ts = -1;
    }

    break;

  case END:

    std::cout << "standupAction : END" << std::endl;
    if((fabs(ACC_Sum[1]) > 9.0 && fabs(ACC_Sum[1]) < 15) ||
        (fabs(ACC_Sum[0]) > 9.0 && fabs(ACC_Sum[0]) < 15)){
      //falling
      std::cout << "I'm still falling" << std::endl;

      if(actiontype == 0){
      	actiontype = 1;
	      ts = -1;
	      state = READY;
      }else if(actiontype == 1){
	      actiontype = 0;
	      ts = -1;
	      state = READY;
      }else{
	      std::cout << "standupAction : END : unknown" << std::endl;
      }

    }else{  // standed
      std::cout << "I'm standed" << std::endl;
      finish_flag = true;
      ts = 0;
      actiontype = -1;
      state = READY;
    }
    break;
  }

  ts++;

  return angleToString();
}
