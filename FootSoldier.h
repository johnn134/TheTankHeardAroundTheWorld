/*
* FootSoldier.h
*/

#ifndef __FOOTSOLDIER_H__
#define __FOOTSOLDIER_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class FootSoldier : public df::Object {
private:

public:
	FootSoldier(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif