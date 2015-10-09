#include "Score.h"

int Score::eventHandler(const df::Event *p_e){
	//let parent handle view events
	if (df::ViewObject::eventHandler(p_e))
		return 1;

	//event ignored
	return 0;
}

Score::Score(){
	setLocation(df::BOTTOM_LEFT);
	setViewString(SCORE_STRING);
	setColor(df::BLACK);
	setValue(0);
}