

#ifndef BRAINMANAGER_H_
#define BRAINMANAGER_H_

#include <iostream>
#include <queue>
#include "BrainBase.h"
#include "TestBrain.h"
#include "world.h"
#include "action.h"

class BrainManager {
public:
	BrainManager();
	virtual ~BrainManager();
	void getAct(Action& act, World& w);
	void updateBrainList(World& w,std::deque<BrainBase*>& BrainList);
	std::deque<BrainBase*> brainList;

};

#endif /* BRAINMANAGER_H_ */
