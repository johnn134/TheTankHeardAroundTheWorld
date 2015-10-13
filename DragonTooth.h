/*
* DragonTooth.h
*/

#ifndef __DRAGONTOOTH_H__
#define __DRAGONTOOTH_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

const int DRAGONTOOTH_POINTS = 1;

class DragonTooth : public df::Object {
private:
	void hit(const df::EventCollision *p_collision_event);

public:
	DragonTooth(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif