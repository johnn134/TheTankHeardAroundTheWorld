//big cannon shot

#ifndef __PLAYER_CANNON_SHOT_H__
#define __PLAYER_CANNON_SHOT_H__

#include "Object.h"
#include "EventCollision.h"

class PlayerCannonShot : public df::Object {

private:
	//out of bounds
	void out();

public:
	PlayerCannonShot(df::Position tank_pos);
	int eventHandler(const df::Event *p_e);
};
#endif