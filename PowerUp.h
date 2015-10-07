//power up for tank

#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Object.h"
#include "Position.h"

class PowerUp : public df::Object{
private:
	std::string ability;

public:
	//give power up an ability
	PowerUp(std::string init_ability, df::Position p);
};
#endif