/*
* MediumRock.h
*/

#ifndef __MEDIUMROCK_H__
#define __MEDIUMROCK_H__

//Dragonfly Headers
#include "EventCollision.h"
#include "Object.h"
#include "Position.h"

const int MEDIUMROCK_POINTS = 2;

class MediumRock : public df::Object {
private:
	int hit_countdown;
	int hit_slowdown;
	int health;
	bool was_hit;
	bool has_flashed;

	void step();
	void hit(const df::EventCollision *p_collision_event);

	//draw frames to match where the player is
	void draw(void);

public:
	MediumRock(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif