/*
 * BrainManager.cpp
 *
 *  Created on: 2012/08/28
 *      Author: kenji
 */

#include "BrainManager.h"

BrainManager::BrainManager() {
}

BrainManager::~BrainManager() {

}

void BrainManager::getAct(Action& act ,World& w){
	if(brainList.size() <= 0){
		updateBrainList(w,brainList);
	}
	BrainBase* nowBrain = brainList.front();
	if( nowBrain->isClear() ){
		//std::cout << "isClear" << std::endl;
		delete nowBrain;
		brainList.pop_front();
		if(brainList.size() <= 0){
			updateBrainList(w,brainList);
		}
		nowBrain = brainList.front();
	}

	nowBrain->getAction(act,w);
	std::cout << "nowBrain is " << nowBrain->getName() << std::endl;
	std::cout << "nowAction is " << act.getName() << std::endl;

}

void BrainManager::updateBrainList(World& w,std::deque<BrainBase*>& brainList){
	//TODO write conditional branch for player position
	TestBrain* b = new TestBrain();
	b->getBrainList(w,brainList);
}
