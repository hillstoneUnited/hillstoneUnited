
#ifndef FALLDOWNRESPONCE_H_
#define FALLDOWNRESPONCE_H_

#include "ResponceBase.h"

class FallDownResponce : ResponceBase{
public:
	FallDownResponce();
	virtual ~FallDownResponce();
	Action responce(World& w);
	bool check(World& w);
};

#endif /* FALLDOWNRESPONCE_H_ */
