/*
* LevelOne.h
*/

#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__

//Dragonfy Includes
#include "Object.h"
#include "ObjectList.h"

//Game Includes
#include "Health.h"
#include "Score.h"
#include "Tank.h"
#include "Lives.h"

class LevelTwo : public df::ViewObject {
private:
	int final_score;
	Tank *p_t;
	Health *p_h;
	Score *p_s;
	Lives *p_l;
	df::ObjectList level_objects;

	void createLevel();
	void createPlayer();
	void clearLevel();

public:
	LevelTwo();
	int eventHandler(const df::Event *p_e);
	void draw();
};
#endif