//view object to show the player's health

#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "ViewObject.h"
#include "Event.h"

#define HEALTH_STRING "HP: "

class Health : public df::ViewObject{
private:

public:
	Health();
	int eventHandler(const df::Event *p_e);
};
#endif