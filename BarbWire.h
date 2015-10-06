/*
* BarbWire.h
*/

#ifndef __BARBWIRE_H__
#define __BARBWIRE_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class BarbWire : public df::Object {
private:

public:
	BarbWire(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif