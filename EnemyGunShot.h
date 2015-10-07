/*
* EnemyGunShot.h
*/

#ifndef __ENEMYGUNSHOT_H__
#define __ENEMYGUNSHOT_H__

//Game Headers
#include "EventCollision.h"
#include "Object.h"

class EnemyGunShot : public df::Object {
private:
	void out();
	void hit(const df::EventCollision *p_collision_event);

public:
	EnemyGunShot(df::Position p);
	int eventHandler(const df::Event *p_e);
};
#endif