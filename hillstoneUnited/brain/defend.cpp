#include "defend.hpp"

Defend::Defend(World& w, double _initpos[]){
  finish_flag = false;
  //  beam_flag = true;

  ballpos[0] = 0.0;
  ballpos[1] = 0.0;
  bal[0] = w.getBAL(0);
  bal[1] = w.getBAL(1);
  bal[2] = w.getBAL(2);
  mypos[0] = 0.0;
  mypos[1] = 0.0;
  balposconf = w.confBAL();
  myposconf = w.confXY();
  angle = w.getABSANGLE();

  field_x = w.getFieldLengthX();
  field_y = w.getFieldLengthY();

  initpos[0] = _initpos[0];
  initpos[1] = _initpos[1];
  initpos[2] = _initpos[2];
  elementList.push_back(new SequenceMovement("LAROUND"));
}

void Defend::judgement(World& w){

  ballpos[0] = w.getBXY(0);
  ballpos[1] = w.getBXY(1);
  bal[0] = w.getBAL(0);
  bal[1] = w.getBAL(1);
  bal[2] = w.getBAL(2);
  mypos[0] = w.getXY(0);
  mypos[1] = w.getXY(1);
  balposconf = w.confBAL();
  myposconf = w.confXY();
  angle = w.getABSANGLE();
  
  if(inTerritory()){
    if(balposconf==300 && myposconf==300){
      elementList.push_back(new TicktackBase("TLEFT", 2));
    }
    else if(balposconf==300){
      elementList.push_back(new SequenceMovement("LAROUND"));
    }
    else{
      if(close2Bal() && towardEnemy()){
	elementList.push_back(new TicktackBase("FORWARD", 10));
  	elementList.push_back(new GABase("GA_FORWARD", 50));

      }else{
  	elementList.push_back(new RunToBall(w));

      }
    }
  }else{
    if(balposconf==300 && myposconf==300){
      elementList.push_back(new SequenceMovement("LAROUND"));
    }
    else{
      double home[2];
      for(int i=0; i<2; i++){
  	home[i] = initpos[i];
      }
      elementList.push_back(new RunTo(w, home));
    }
  }
   elementList.push_back(new SequenceMovement("LAROUND"));

}

bool Defend::inTerritory(){
  if(abs(ballpos[0] - mypos[0]) < 6.0 &&
     abs(ballpos[1] - mypos[1]) < 6.0){
    return true;
  }else{
    return false;
  }
}

bool Defend::atHome(){
  if(abs(mypos[0] - initpos[0]) < 0.5 &&
     abs(mypos[1] - initpos[1]) < 0.5){
    return true;
  }else{
    return false;
  }
}

bool Defend::close2Bal(){
  if(abs(bal[0]) < 0.7 &&
     abs(bal[0]) < 0.7){
    return true;
  }else{
    return false;
  }
}

bool Defend::towardEnemy(){
  if(abs(angle) < 60){
    return true;
  }else{
    return false;
  }
}

bool Defend::inDanger(){
  if(ballpos[0] < -(1*field_x/3)){
    return true;
  }else{
    return false;
  }
}

void Defend::updateFinishFlag(World& w){
  if(!inTerritory() && atHome()){
    finish_flag = true;
  }else{
    finish_flag = false;
  }
}

