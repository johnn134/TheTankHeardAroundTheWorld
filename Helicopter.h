/*
* Helicopter.h
*/

#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class Helicopter : public df::Object {
private:
	int fire_slowdown;
	int fire_countdown;
	int anim_slowdown;
	int anim_countdown;
	int health;
	bool flying_right;
	bool first_frame;

	void fire();
	void step();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	Helicopter(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif