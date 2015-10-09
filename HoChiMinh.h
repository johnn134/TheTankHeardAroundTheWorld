/*
* HoChiMinh.h
*/

#ifndef __HOCHIMINH_H__
#define __HOCHIMINH_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "FootSoldier.h"
#include "Object.h"
#include "Position.h"

const int HOCHIMINH_HEALTH = 3;

class HoChiMinh : public df::Object {
private:
	df::Object *player;
	df::Object *soldier1;
	df::Object *soldier2;
	df::Object *soldier3;
	int health;
	int fire_slowdown;
	int fire_countdown;
	bool in_position;
	bool mouth_open;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	HoChiMinh(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);

	//Confirm that soldier is dead
	void soldierDied(df::Object *s);
};
#endif