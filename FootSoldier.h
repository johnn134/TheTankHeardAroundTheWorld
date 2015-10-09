/*
* FootSoldier.h
*/

#ifndef __FOOTSOLDIER_H__
#define __FOOTSOLDIER_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "HoChiMinh.h"
#include "Object.h"
#include "Position.h"

class FootSoldier : public df::Object {
private:
	df::Object *player;
	df::Object *boss;
	int fire_slowdown;
	int fire_countdown;
	bool paused;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	FootSoldier(df::Position p, df::Object *new_player);
	FootSoldier(df::Position p, df::Object *new_player, df::Object *new_boss);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);

	//Set whether the gameobject is paused or not
	void setPause(bool new_pause);
};
#endif