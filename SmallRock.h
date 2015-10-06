/*
* SmallRock.h
*/

#ifndef __SMALLROCK_H__
#define __SMALLROCK_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class SmallRock : public df::Object {
private:

public:
	SmallRock(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif