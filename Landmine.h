/*
* Landmine.h
*/

#ifndef __LANDMINE_H__
#define __LANDMINE_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Landmine : public df::Object {
private:

public:
	Landmine(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif