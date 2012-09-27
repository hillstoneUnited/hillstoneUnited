

#ifndef BRAINBASE_H_
#define BRAINBASE_H_

#include <string>
#include <iostream>

#include "action.h"
#include "world.h"
#include "util.h"
#include <queue>

class BrainBase {
public:
	BrainBase();
	virtual ~BrainBase();
	virtual void getBrainList(World& w, std::deque<BrainBase*>& brainList); //get brainList
	virtual void getActionList(World& w);
	virtual void getAction(Action& act, World& w);
	void setClear(bool cflag);
	bool isClear();
	void setName(std::string name);
	void setAction(Action act, ActionName name, int count);
	std::string getName();

	virtual void hoge();
protected:
	bool isClearFlag;
	std::deque<Action> actionList;
	std::string brainName;
};

#endif /* BRAINBASE_H_ */
