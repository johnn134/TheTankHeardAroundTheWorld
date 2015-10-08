//power up for tank

#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Object.h"
#include "Position.h"

enum Ability{
	UNDEFINED_ABILITY = -1,
	WIDE_SHOT,
	CANNON_CDR,
	ANGLE_CANNON,
	HEALTH_GET,
};

class PowerUp : public df::Object{
private:
	Ability ability;
	

public:
	Ability getAbility() const;
	//give power up an ability
	PowerUp(Ability init_ability, df::Position p);
};
#endif