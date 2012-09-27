

#ifndef RESPONCEBASE_H_
#define RESPONCEBASE_H_

#include "world.h"
#include "action.h"
#include "util.h"

class ResponceBase {
public:
	ResponceBase();
	virtual ~ResponceBase();
	virtual Action responce(World& w); //do Action at sudden situation
	virtual bool check(World& w);
};

#endif /* RESPONCEBASE_H_ */
