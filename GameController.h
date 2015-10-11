/*
* GameController.h
*/

#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

//Dragonfly Headers
#include "ViewObject.h"

/* 
* Levels
* 0 - start screen
* 1 - level select
* 2 - how to play
* 3 - level 1
* 4 - level 2
* 5 - level 3
* 6 - level 4
*/

class GameController : public df::ViewObject {
private:
	int cur_level;
	int selection;
	int level_scores[4];
	bool level_unlocked[4];

	//Load the given level into the game
	void loadLevel(int new_level);

	//Read the game info from "gameinfo.txt"
	//If gameinfo.txt does not exist, create it
	//Return 0 if read or created correctly, -1 else
	int getGameInfo();

	//Read the unlocked levels from "gameinfo.txt"
	//Return 0 if read, -1 else
	int getUnlockedLevels();

	//Read the highscores for each level from "gameinfo.txt"
	//Return 0 if read, -1 else
	int getLevelHighscores();

	void moveSelection(int new_selection);

public:
	GameController();
	int eventHandler(const df::Event *p_e);
	void draw();
};
#endif