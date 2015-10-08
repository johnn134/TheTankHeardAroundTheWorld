//big cannon shot

#ifndef __PLAYER_CANNON_SHOT_H__
#define __PLAYER_CANNON_SHOT_H__

#include "Object.h"
#include "EventCollision.h"

class PlayerCannonShot : public df::Object {

private:
	//out of bounds
	void out();

	//collided with something
	void hit(const df::EventCollision *p_event_collision);

public:
	PlayerCannonShot(df::Position tank_pos);
	//~PlayerCannonShot();
	int eventHandler(const df::Event *p_e);
};
#endif