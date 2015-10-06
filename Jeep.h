/*
* Jeep.h
*/

#ifndef __JEEP_H__
#define __JEEP_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Jeep : public df::Object {
private:

public:
	Jeep(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif