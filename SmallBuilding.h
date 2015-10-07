/*
* SmallBuilding.h
*/

#ifndef __SMALLBUILDING_H__
#define __SMALLBUILDING_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class SmallBuilding : public df::Object {
private:
	int hit_countdown;
	int hit_slowdown;
	int health;
	bool was_hit;
	bool has_flashed;

	void step();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	SmallBuilding(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif