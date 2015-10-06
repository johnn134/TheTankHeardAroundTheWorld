/*
* DragonTooth.h
*/

#ifndef __DRAGONTOOTH_H__
#define __DRAGONTOOTH_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class DragonTooth : public df::Object {
private:

public:
	DragonTooth(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif