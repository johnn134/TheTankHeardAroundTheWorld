/*
* EnemyBombShot.h
*/

#ifndef __ENEMYBOMBSHOT_H__
#define __ENEMYBOMBSHOT_H__

//Game Headers
#include "EventCollision.h"
#include "Object.h"

const int BOMB_LIFE = 10;

class EnemyBombShot : public df::Object {
private:
	int time_to_live;

	void step();

public:
	EnemyBombShot(df::Position p);
	int eventHandler(const df::Event *p_e);
};

#endif