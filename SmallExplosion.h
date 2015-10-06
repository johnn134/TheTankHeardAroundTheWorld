/*
* SmallExplosion.h
*/

#ifndef __SMALLEXPLOSION_H__
#define __SMALLEXPLOSION_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class SmallExplosion : public df::Object {
private:
	int time_to_live;
	void step();

public:
	SmallExplosion(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif