/*
* HoChiMinh.h
*/

#ifndef __HOCHIMINH_H__
#define __HOCHIMINH_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "EventFootSoldierDeath.h"
#include "Object.h"
#include "Position.h"

const int HOCHIMINH_HEALTH = 3;
const int HOCHIMINH_POINTS = 100;

class HoChiMinh : public df::Object {
private:
	df::Object *player;
	df::Object *soldier1;
	df::Object *soldier2;
	df::Object *soldier3;
	df::Object *soldier4;
	df::Object *soldier5;
	df::Object *mortar1;
	df::Object *mortar2;
	int health;
	int fire_slowdown;
	int fire_countdown;
	int mortar_slowdown;
	int mortar_countdown;
	bool in_position;
	bool mouth_open;

	void step();
	void fire();
	void refillMortars();
	void hit(const df::EventCollision *p_collision_event);
	void soldierDied(const EventFootSoldierDeath *p_death_event);

	//draw frames to match where the player is
	void draw(void);

public:
	HoChiMinh(df::Position p, df::Object *new_player);
	~HoChiMinh();

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif