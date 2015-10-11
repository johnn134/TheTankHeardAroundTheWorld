/*
* EnemyTank.h
*/

#ifndef __ENEMYTANK_H__
#define __ENEMYTANK_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

class EnemyTank : public df::Object {
private:
	df::Object *player;
	int fire_slowdown;
	int fire_countdown;
	int move_slowdown;
	int move_countdown;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);
	void move(int dx);

public:
	EnemyTank(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif