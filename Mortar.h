/*
* Mortar.h
*/

#ifndef __MORTAR_H__
#define __MORTAR_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

const int MORTAR_UNOCCUPY_POINTS = 5;
const int MORTAR_DESTROY_POINTS = 10;

class Mortar : public df::Object {
private:
	df::Object *player;
	int fire_slowdown;
	int fire_countdown;
	int firing_anim_slowdown;
	int firing_anim_countdown;
	bool occupied;
	bool firing;

	void fire();
	void step();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	Mortar(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif