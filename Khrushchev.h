/*
* Khrushchev.h
*/

#ifndef __KHRUSHCHEV_H__
#define __KHRUSHCHEV_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "EventFootSoldierDeath.h"
#include "FootSoldier.h"
#include "Object.h"
#include "Position.h"

const int KHRUSHCHEV_HEALTH = 100;
const int KHRUSHCHEV_POINTS = 250;

class Khrushchev : public df::Object {
private:
	df::Object *player;
	df::Object *jeepL;
	df::Object *jeepR;
	df::Object *tankM;
	int health;
	int health_left;
	int health_right;
	int fire_slowdown;
	int fire_countdown;
	float move_speed;
	bool in_position;
	bool going_left;
	int jeep_countdown;
	int tank_countdown;

	void step();
	void fire();
	void hit(const df::EventCollision *p_collision_event);
	void soldierDied(const EventFootSoldierDeath *p_death_event);
	void checkMove();
	void makeJeep(bool left_jeep);

	//draw frames to match where the player is
	void draw(void);

public:
	Khrushchev(df::Position p, df::Object *new_player);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif