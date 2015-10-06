/*
* Mortar.h
*/

#ifndef __MORTAR_H__
#define __MORTAR_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class Mortar : public df::Object {
private:

public:
	Mortar(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif