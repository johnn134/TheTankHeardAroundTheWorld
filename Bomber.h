/*
* Bomber.h
*/

#ifndef __BOMBER_H__
#define __BOMBER_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class Bomber : public df::Object {
private:
	int fire_slowdown;
	int fire_countdown;
	bool bomb_right;
	bool paused;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);

public:
	Bomber(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);

	//Set whether the gameobject is paused or not
	void setPause(bool new_pause);
};
#endif