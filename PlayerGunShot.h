//PlayerGunShot that the player shoots

#ifndef __PLAYER_GUN_SHOT_H__
#define __PLAYER_GUN_SHOT_H__

#include "Object.h"
#include "EventCollision.h"

class PlayerGunShot : public df::Object {

private:
	//out of bounds
	void out();

	//collision
	void hit(const df::EventCollision *p_collision_event);

public:
	PlayerGunShot(df::Position tank_pos);
	int eventHandler(const df::Event *p_e);
};
#endif