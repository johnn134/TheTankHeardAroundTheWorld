/*
* TankTrap.h
*/

#ifndef __TANKTRAP_H__
#define __TANKTRAP_H__

//Dragonfly Headers
#include "Object.h"
#include "Position.h"

class TankTrap : public df::Object {
private:

public:
	TankTrap(df::Position p);

	// Handle event.
	// Return 0 if ignored, else 1.
	int eventHandler(const df::Event *p_e);
};
#endif