

#include "ResponceBase.h"

ResponceBase::ResponceBase() {
	// TODO Auto-generated constructor stub

}

ResponceBase::~ResponceBase() {
	// TODO Auto-generated destructor stub
}

Action ResponceBase::responce(World& w){
	//pass
	return Action(DUMMY);
}
bool ResponceBase::check(World& w){
	//pass
	return false;
}
