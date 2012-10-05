/*
 * FallDownResponce.cpp
 *
 *  Created on: 2012/08/30
 *      Author: kenji
 */

#include "FallDownResponce.h"
#include <math.h>

FallDownResponce::FallDownResponce() {
	// TODO Auto-generated constructor stub

}

FallDownResponce::~FallDownResponce() {
	// TODO Auto-generated destructor stub
}

Action FallDownResponce::responce(World& w){
	Action sp = Action(STANDUP);
	return sp;
}

bool FallDownResponce::check(World& w){
	//check whether agent is fallen down
	const int limen = 10;
	double ACC_Sum[2];
	ACC_Sum[0] = w.getACC_Sum(0,limen);
	ACC_Sum[1] = w.getACC_Sum(1,limen);

  if((fabs(ACC_Sum[1]) > 9.0 * limen) && (fabs(ACC_Sum[1]) < 15 * limen)){
  	std::cout << "I'm utsubuse!" << std::endl;
    return true; //utsubuse or aomuki
  }

  if((fabs(ACC_Sum[0]) > 9.0 * limen) && (fabs(ACC_Sum[0]) < 15 * limen)){
  	std::cout << "I'm yokomuki" << std::endl;
    return true; //yokomuki
  }

  std::cout << "not FallDown" << std::endl;
  return false;
}
