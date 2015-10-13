/*
* GameController.cpp
*/

//System Headers
#include <sstream>
#include <string>

//Dragonfly Headers
#include "EventKeyboard.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ObjectList.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "Bomber.h"
#include "EnemyTank.h"
#include "EventLevelHandled.h"
#include "FootSoldier.h"
#include "GameController.h"
#include "Helicopter.h"
#include "Jeep.h"
#include "LevelOne.h"
#include "Mortar.h"
#include "RocketSoldier.h"

GameController::GameController() {

	setType("GameController");

	setLocation(df::CENTER_CENTER);

	// Register for "keyboard" event.
	registerInterest(df::KEYBOARD_EVENT);

	//Register for "levelchange" event
	registerInterest(LEVELHANDLED_EVENT);

	cur_level = 0;
	selection = 0;

	//Get unlocked levels
	if (getGameInfo()) {
		df::LogManager::getInstance().writeLog("GameController::GameController(): Failed to read game info from \"gameinfo.txt\"");
	}
}

int GameController::eventHandler(const df::Event *p_e) {
	df::GameManager &game_manager = df::GameManager::getInstance();

	//only check keyboard events on the start screen and level select

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
		if (cur_level == 0) {
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				switch (p_keyboard_event->getKey()) {
				case df::Keyboard::RETURN:			//Load selected level
					if (selection == 2)
						df::GameManager::getInstance().setGameOver(true);
					else
						loadLevel(selection + 1);
					break;
				case df::Keyboard::W:			//Move selection up
					moveSelection(selection - 1);
					break;
				case df::Keyboard::S:		//Move selection down
					moveSelection(selection + 1);
					break;
				default:
					break;
				}
			}
		}
		else if (cur_level == 1) {
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				switch (p_keyboard_event->getKey()) {
				case df::Keyboard::RETURN:
					if (selection == 3)
						loadLevel(0);
					else
						loadLevel(selection + 3);	//Load selected level
					break;
				case df::Keyboard::W:			//Move selection up
					moveSelection(selection - 1);
					break;
				case df::Keyboard::S:		//Move selection down
					moveSelection(selection + 1);
					break;
				default:
					break;
				}
			}
		}
		else if (cur_level == 2) {
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				switch (p_keyboard_event->getKey()) {
				case df::Keyboard::RETURN:		//Return to Main Menu
					loadLevel(0);
					break;
				default:
					break;
				}
			}
		}
		return 1;
	}

	if (p_e->getType() == LEVELHANDLED_EVENT) {
		EventLevelHandled *p_keyboard_event = (EventLevelHandled *)p_e; 
		
		//If level was completed, record highscore and unlock next level
		if (p_keyboard_event->levelCompleted()) {
			//Unlock next level
			if (cur_level >= 3 && cur_level < 5) {
				level_unlocked[cur_level - 3] = true;
			}

			//Check if new highscore
			if (level_scores[cur_level - 3] < p_keyboard_event->getScore()) {
				level_scores[cur_level - 3] = p_keyboard_event->getScore();
			}
		}

		//Return to level select screen
		loadLevel(1);

		return 1;
	}

	return 0;
}

//Load the given level into the game
void GameController::loadLevel(int new_level) {
	cur_level = new_level;
	if (cur_level == 0) {
		selection = 0;
	}
	else if (cur_level == 1) {
		selection = 0;
	}
	else if (cur_level == 3) {
		//Level 1
		new LevelOne();
	}
	else if (cur_level == 4) {
		//Level 2
		//new LevelTwo();
	}
	else if (cur_level == 5) {
		//Level 3
		//new LevelThree();
	}
}

//Read the game info from "gameinfo.txt"
//If gameinfo.txt does not exist, create it
//Return 0 if read or created correctly, -1 else
int GameController::getGameInfo() {
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Open "gameinfo.txt"

	//read the unlocked levels
	if (getUnlockedLevels()) {
		log_manager.writeLog("GameController::getGameInfo(): Failed to read unlocked levels from \"gameinfo.txt\"");
	}

	//read level highscores
	if (getLevelHighscores()) {
		log_manager.writeLog("GameController::getGameInfo(): Failed to read highscores from \"gameinfo.txt\"");
	}

	return 0;
}

//Read the unlocked levels from "gameinfo.txt"
//Return 0 if read, -1 else
int GameController::getUnlockedLevels() {
	level_unlocked[0] = true;
	for (int i = 1; i < NUM_LEVELS; i++) {
		level_unlocked[i] = false;
	}
	return 0;
}

//Read the highscores for each level from "gameinfo.txt"
//Return 0 if read, -1 else
int GameController::getLevelHighscores() {
	for (int i = 0; i < NUM_LEVELS; i++) {
		level_scores[i] = 0;
	}
	return 0;
}

void GameController::moveSelection(int new_selection) {
	if (cur_level == 0) {
		if (new_selection < 0)
			selection = 0;
		else if (new_selection > 2)
			selection = 2;
		else
			selection = new_selection;
	}
	else if (cur_level == 1) {
		if (new_selection < 0)
			selection = 0;
		else if (new_selection > NUM_LEVELS)
			selection = NUM_LEVELS;
		else
			selection = new_selection;
	}
}

void GameController::draw() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::Position mid_pos = df::Position(world_manager.getView().getCorner().getX() + world_manager.getView().getHorizontal() / 2,
		world_manager.getView().getCorner().getY() + world_manager.getView().getVertical() / 2);
	int mid_x = world_manager.getView().getCorner().getX() + world_manager.getView().getHorizontal() / 2;
	int mid_y = world_manager.getView().getCorner().getY() + world_manager.getView().getVertical() / 2;
	int left_margin = 5;
	int arrow_x = left_margin + 2;

	if (cur_level == 0) {
		//Draw Start Screen
		df::Sprite *p_temp_sprite = df::ResourceManager::getInstance().getSprite("titlescreenimage");
		graphics_manager.drawFrame(df::Position(mid_x, mid_y), p_temp_sprite->getFrame(0), true);

		graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 4), "Level Select",
			df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 2), "How To Play",
			df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 0), "Quit to Desktop",
			df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);

		//Draw selection arrow
		graphics_manager.drawString(df::Position(mid_x - arrow_x, mid_y - 4 + selection * 2), ">", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
	}
	else if (cur_level == 1) {
		//Level Select Screen
		graphics_manager.drawString(df::Position(mid_x, mid_y - 5), "Level Select", df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);

		//Vietnam
		if (level_unlocked[0]) {
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 3), "Vietnam", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
			std::ostringstream h_s;
			h_s << "highscore: " << level_scores[0];
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 2), h_s.str(), df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		}

		//Russia
		if (level_unlocked[1]) {
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y), "Russia", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
			std::ostringstream h_s;
			h_s << "highscore: " << level_scores[1];
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 1), h_s.str(), df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		}
		else {
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y), "?????", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 1), "highscore: 0", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);

		}

		//The USA
		if (level_unlocked[3]) {
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 3), "The United States of America", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
			std::ostringstream h_s;
			h_s << "highscore: " << level_scores[3];
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 4), h_s.str(), df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		}
		else {
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 3), "?????", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
			graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 4), "highscore: 0", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
		}
		//Back
		graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y + 6), "Back", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);

		//Draw selection arrow
		graphics_manager.drawString(df::Position(mid_x - arrow_x, mid_y - 3 + selection * 3), ">", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
	}
	else if (cur_level == 2) {
		//How to play
		graphics_manager.drawString(df::Position(mid_x, mid_y - 5), "How To Play", df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);
		graphics_manager.drawString(df::Position(mid_x, mid_y - 3), "WASD to move, mouse click to fire machinegun, space to fire cannon",
			df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);

		graphics_manager.drawString(df::Position(mid_x - left_margin, mid_y - 1), "Back",
			df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);

		//Draw selection arrow
		graphics_manager.drawString(df::Position(mid_x - arrow_x, mid_y - 1), ">", df::Justification::LEFT_JUSTIFIED, df::Color::BLACK);
	}
}