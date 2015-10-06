/*
* EnemyTank.h
*/

#ifndef __ENEMYTANK_H__
#define __ENEMYTANK_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class EnemyTank : public df::Object {
private:

public:
	EnemyTank(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif