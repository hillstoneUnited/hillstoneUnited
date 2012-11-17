
#include "TestBrain.h"

TestBrain::TestBrain() {
	setName("TestBrain");
}

TestBrain::~TestBrain() {
	// TODO Auto-generated destructor stub
}

void TestBrain::hoge(){
	std::cout << "hogehogehoge" << std::endl;
}

void TestBrain::getActionList(World& w){
	std::cout << "create ActionList " << std::endl;
	if( fdr.check(w) ){
		actionList.push_front( fdr.responce(w) );
	}
	Action act = Action(FFWALK);
	act.setCount(30);
	actionList.push_back(act);
}

void TestBrain::getBrainList(World& w, std::deque<BrainBase*>& brainList){ //TODO get??
	getActionList(w);
	std::cout << "actions = " << actionList.size() << std::endl;
	brainList.push_back(this);
}

void TestBrain::getAction(Action& act, World& w){

	if( fdr.check(w) ){
		actionList.push_front( fdr.responce(w) );
		act = actionList.front();
	}
	else{
		if( act.isFinished() ){

			if(actionList.size() > 0){
				act = actionList.front();
				actionList.pop_front();
			}
			else{
				std::cout << "ActionList is empty!! return DUMMY set Clear" << std::endl;
				setClear(true);
        act = Action(LAROUND);
			}

		}
	}

	/*
	if(actionList.size() > 0){
		actionList[0] = act;
	}

	if( fdr.check(w) ){
		actionList.push_front( fdr.responce(w) );
	}

	if(actionList.size() <= 0){
		std::cout << "[error]actionList is empty!! return DUMMY" << std::endl;
		Action tempAction = Action(DUMMY);
		act = tempAction;
	}

	if(actionList[0].getCount() <= 0){
		std::cout << "now action is ended!!" << std::endl;
		actionList.pop_front();
	}
	if(actionList.size() <= 0){
		std::cout << "all action is done!! return DUMMY set Clear" << std::endl;
		setClear(true);
		Action tempAction = Action(DUMMY);
		act = tempAction;
	}

	std::cout << "remain count = " << actionList[0].getCount() << std::endl;

	act = actionList[0];
	*/

}
