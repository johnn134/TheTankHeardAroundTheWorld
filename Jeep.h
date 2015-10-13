/*
* Jeep.h
*/

#ifndef __JEEP_H__
#define __JEEP_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

const int ANIMATION_DELAY = 15;
const int HEALTH = 5;
const int JEEP_POINTS = 20;

class Jeep : public df::Object {
private:
	df::Object *player;
	int fire_slowdown;
	int fire_countdown;
	int hit_countdown;
	int hit_slowdown;
	int anim_slowdown;
	int anim_countdown;
	int curFrame;
	int health;
	bool was_hit;
	bool has_flashed;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	Jeep(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif