#include "Lives.h"

int Lives::eventHandler(const df::Event *p_e){
	//let parent handle view events
	if (df::ViewObject::eventHandler(p_e))
		return 1;

	//event ignored
	return 0;
}

Lives::Lives(){
	setLocation(df::BOTTOM_CENTER);
	setViewString(LIVES_STRING);
	setColor(df::BLACK);
}