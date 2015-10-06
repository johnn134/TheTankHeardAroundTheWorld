/*
* Helicopter.h
*/

#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Helicopter : public df::Object {
private:

public:
	Helicopter(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif