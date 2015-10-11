/*
* LevelOne.h
*/

#ifndef __LEVELONE_H__
#define __LEVELONE_H__

//Dragonfy Includes
#include "Object.h"
#include "ObjectList.h"

//Game Includes
#include "Health.h"
#include "Score.h"
#include "Tank.h"

const float SCROLL_SPEED = 0.20f;

class LevelOne : public df::ViewObject {
private:
	int final_score;
	Tank *p_t;
	Health *p_h;
	Score *p_s;
	df::ObjectList level_objects;

	void createLevel();
	void createPlayer();
	void clearLevel();

public:
	LevelOne();
	int eventHandler(const df::Event *p_e);
	void draw();
};
#endif