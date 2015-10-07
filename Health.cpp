#include "Health.h"

int Health::eventHandler(const df::Event *p_e){
	//let parent handle view events
	if (df::ViewObject::eventHandler(p_e))
		return 1;

	//event ignored
	return 0;
}

Health::Health(){
	setLocation(df::BOTTOM_RIGHT);
	setViewString(HEALTH_STRING);
	setColor(df::BLACK);
	setValue(10);
}