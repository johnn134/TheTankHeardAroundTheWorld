/*
* GameController.h
*/

#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

//Dragonfly Headers
#include "ViewObject.h"

class GameController : public df::ViewObject {
private:
	bool paused;
	void pause();
	void play();

public:
	GameController();
	int eventHandler(const df::Event *p_e);
	void draw();
};
#endif