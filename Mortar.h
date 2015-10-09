/*
* Mortar.h
*/

#ifndef __MORTAR_H__
#define __MORTAR_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class Mortar : public df::Object {
private:
	df::Object *player;
	int fire_slowdown;
	int fire_countdown;
	int firing_anim_slowdown;
	int firing_anim_countdown;
	bool occupied;
	bool firing;
	bool paused;

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

	//Set whether the gameobject is paused or not
	void setPause(bool new_pause);
};
#endif