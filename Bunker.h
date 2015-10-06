/*
* Bunker.h
*/

#ifndef __BUNKER_H__
#define __BUNKER_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Bunker : public df::Object {
private:

public:
	Bunker(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif