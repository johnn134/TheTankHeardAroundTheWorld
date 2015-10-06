/*
* Trench.h
*/

#ifndef __TRENCH_H__
#define __TRENCH_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Trench : public df::Object {
private:

public:
	Trench(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif