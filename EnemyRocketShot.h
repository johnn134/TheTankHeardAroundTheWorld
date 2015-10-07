/*
* EnemyRocketShot.h
*/

#ifndef __ENEMYROCKETSHOT_H__
#define __ENEMYROCKETSHOT_H__

//Game Headers
#include "EventCollision.h"
#include "Object.h"

class EnemyRocketShot : public df::Object {
private:
	void out();
	void hit(const df::EventCollision *p_collision_event);

public:
	EnemyRocketShot(df::Position p);
	int eventHandler(const df::Event *p_e);
};

#endif