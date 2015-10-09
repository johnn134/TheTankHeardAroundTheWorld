//place holder for bombers, jeeps and helicopters until they appear on screen

#ifndef __EGG_H__
#define __EGG_H__

#include "Object.h"
#include "Event.h"

#define EGG_CHAR 'O'

class Egg : public df::Object{
private:
	std::string eggType;
	df::Object *target;
	void step();
	void draw(void);

public:
	//(object you want to hatch, position of the egg, target player tank)
	Egg(std::string objType, df::Position eggPos, df::Object *new_player);
	int eventHandler(const df::Event *p_e);
};
#endif