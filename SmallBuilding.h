/*
* SmallBuilding.h
*/

#ifndef __SMALLBUILDING_H__
#define __SMALLBUILDING_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class SmallBuilding : public df::Object {
private:

public:
	SmallBuilding(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif