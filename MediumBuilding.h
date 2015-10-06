/*
* MediumBuilding.h
*/

#ifndef __MEDIUMBUILDING_H__
#define __MEDIUMBUILDING_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class MediumBuilding : public df::Object {
private:

public:
	MediumBuilding(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif