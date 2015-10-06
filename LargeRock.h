/*
* LargeRock.h
*/

#ifndef __LARGEROCK_H__
#define __LARGEROCK_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class LargeRock : public df::Object {
private:

public:
	LargeRock(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif