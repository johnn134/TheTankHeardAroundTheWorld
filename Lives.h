//view object to show the player's lives

#ifndef __LIVES_H__
#define __LIVES_H__

#include "ViewObject.h"
#include "Event.h"

#define LIVES_STRING "Lives: "

class Lives : public df::ViewObject{
private:

public:
	Lives();
	int eventHandler(const df::Event *p_e);
};
#endif