/*
* LargeBuilding.h
*/

#ifndef __LARGEBUILDING_H__
#define __LARGEBUILDING_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class LargeBuilding : public df::Object {
private:

public:
	LargeBuilding(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif