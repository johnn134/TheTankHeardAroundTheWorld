/*
* EnemyCannonShot.h
*/

#ifndef __ENEMY_CANNON_SHOT_H__
#define __ENEMY_CANNON_SHOT_H__

//Game Headers
#include "Object.h"
#include "EventCollision.h"

class EnemyCannonShot : public df::Object {
private:
	void out();
	void hit(const df::EventCollision *p_collision_event);

public:
	EnemyCannonShot(df::Position tank_pos);
	int eventHandler(const df::Event *p_e);
};
#endif