/*
* RocketSoldier.h
*/

#ifndef __ROCKETSOLDIER_H__
#define __ROCKETSOLDIER_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class RocketSoldier : public df::Object {
private:
	df::Object *player;
	int fire_slowdown;
	int fire_countdown;
	bool rocketInTube;

	void fire();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	RocketSoldier(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif