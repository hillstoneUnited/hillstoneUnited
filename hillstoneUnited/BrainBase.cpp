/*
 * BrainBase.cpp
 *
 *  Created on: 2012/08/28
 *      Author: kenji
 */

#include "BrainBase.h"

BrainBase::BrainBase(){
	setClear(false);
	setName("BaseBrain");
}

BrainBase::~BrainBase() {
	// TODO Auto-generated destructor stub
}

void BrainBase::setClear(bool flag){
	isClearFlag = flag;
}

bool BrainBase::isClear(){
	return isClearFlag;
}

void BrainBase::getBrainList(World& w, std::deque<BrainBase*>& brainList){
	//pass
}

void BrainBase::getActionList(World& w){
	//pass
}

void BrainBase::getAction(Action& act, World& w){

	std::cout << "getAction of BrainBase is called" << std::endl;

	/*
	getActionList(w);

	if(actionList.size() <= 0){
		std::cout << "action list is empty!! cflag = true, return DUMMY" << std::endl;
		setClear(true);
		Action tempAction = Action();
		tempAction.setName(DUMMY);
		return tempAction;
	}


	Action nowAction = actionList.front();
	if(nowAction.getCount() <= 0){
		actionList.pop_front();
	}
	if(actionList.size() <= 0){
		std::cout << "all action is done!! return DUMMY" << std::endl;
		setClear(true);
		Action tempAction = Action();
		tempAction.setName(DUMMY);
		return tempAction;
	}
	nowAction = actionList.front();
	return nowAction;
	*/
	//return Action(DUMMY);

}

void BrainBase::setAction(Action act, ActionName name, int count){
	//TODO ここにActionにパロメーターセットをかく
}

void BrainBase::setName(std::string name){
	brainName = name;
}

std::string BrainBase::getName(){
	return brainName;
}

void BrainBase::hoge(){
	std::cout << "hoge1" << std::endl;
}
