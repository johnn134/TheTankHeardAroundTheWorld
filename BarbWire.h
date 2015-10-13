/*
* BarbWire.h
*/

#ifndef __BARBWIRE_H__
#define __BARBWIRE_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

const int BARBWIRE_POINTS = 1;

class BarbWire : public df::Object {
private:
	void hit(const df::EventCollision *p_collision_event);

public:
	BarbWire(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif