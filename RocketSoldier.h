/*
* RocketSoldier.h
*/

#ifndef __ROCKETSOLDIER_H__
#define __ROCKETSOLDIER_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class RocketSoldier : public df::Object {
private:

public:
	RocketSoldier(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif