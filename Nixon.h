/*
* Nixon.h
*/

#ifndef __NIXON_H__
#define __NIXON_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "EventFootSoldierDeath.h"
#include "Object.h"
#include "Position.h"

const int NIXON_HEALTH = 20;
const int NIXON_POINTS = 100;

class Nixon : public df::Object {
private:
	df::Object *tank1;
	df::Object *tank2;
	df::Object *tank3;
	df::Object *tank4;
	int health;
	bool in_position;
	bool shielded;

	void step();
	void removeShield();
	void hit(const df::EventCollision *p_collision_event);
	void unitDied(const EventFootSoldierDeath *p_death_event);

	//draw frames to match where the player is
	void draw(void);

public:
	Nixon(df::Position p);
	~Nixon();

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif