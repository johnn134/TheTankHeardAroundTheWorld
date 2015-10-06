/*
* Bomber.h
*/

#ifndef __BOMBER_H__
#define __BOMBER_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Bomber : public df::Object {
private:

public:
	Bomber(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif