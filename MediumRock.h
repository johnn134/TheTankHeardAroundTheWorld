/*
* MediumRock.h
*/

#ifndef __MEDIUMROCK_H__
#define __MEDIUMROCK_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class MediumRock : public df::Object {
private:

public:
	MediumRock(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif