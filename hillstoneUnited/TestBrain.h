
#ifndef TESTBRAIN_H_
#define TESTBRAIN_H_

#include "BrainBase.h"
#include "FallDownResponce.h"

class TestBrain : public BrainBase{
public:
	TestBrain();
	virtual ~TestBrain();
	void getBrainList(World& w,std::deque<BrainBase*>& brainList);
	void getActionList(World& w);
	void getAction(Action& act, World& w);
	void hoge();
private:
	FallDownResponce fdr;
};



#endif /* TESTBRAIN_H_ */
