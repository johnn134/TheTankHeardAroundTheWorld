/*
* LevelThree.cpp
*/

//Dragonfly Headers
#include "WorldManager.h"

//Game includes.
#include "BarbWire.h"
#include "Bomber.h"
#include "DragonTooth.h"
#include "EnemyTank.h"
#include "EventLevelComplete.h"
#include "EventLevelFailed.h"
#include "EventLevelHandled.h"
#include "FootSoldier.h"
#include "Health.h"
#include "Helicopter.h"
#include "HoChiMinh.h"
#include "Jeep.h"
#include "Landmine.h"
#include "LargeBuilding.h"
#include "LargeRock.h"
#include "LevelOne.h"
#include "LevelThree.h"
#include "Lives.h"
#include "MediumBuilding.h"
#include "MediumRock.h"
#include "Mortar.h"
#include "PowerUp.h"
#include "RocketSoldier.h"
#include "SmallBuilding.h"
#include "SmallRock.h"
#include "Tank.h"
#include "TankTrap.h"

LevelThree::LevelThree() {
	setType("LevelThree");

	setLocation(df::CENTER_CENTER);

	//Register interest for 'levelfailed' event
	registerInterest(LEVELFAILED_EVENT);

	//Register interest for 'levelcomplete' event
	registerInterest(LEVELCOMPLETE_EVENT);

	final_score = 0;
	p_t = NULL;
	p_h = NULL;
	p_s = NULL;

	createPlayer();
	createLevel();
}

int LevelThree::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == LEVELCOMPLETE_EVENT) {
		//Clear level gameobjects
		clearLevel();

		//Send completed LevelHandled event to GameController
		EventLevelHandled ev(true, final_score);
		df::WorldManager::getInstance().onEvent(&ev);


		return 1;
	}
	if (p_e->getType() == LEVELFAILED_EVENT) {
		//Clear level gameobjects
		clearLevel();

		//Send failed LevelHandled event to GameController
		EventLevelHandled ev(false, 0);
		df::WorldManager::getInstance().onEvent(&ev);
		df::WorldManager::getInstance().markForDelete(this);
		return 1;
	}
	return 0;
}

void LevelThree::draw() {

}

void LevelThree::clearLevel() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::ObjectList all_objects = world_manager.getAllObjects();

	df::ObjectListIterator li_level(&level_objects);
	df::ObjectListIterator li_game(&all_objects);

	//Delete level objects
	for (li_level.first(); !li_level.isDone(); li_level.next()) {
		for (li_game.first(); !li_game.isDone(); li_game.next()) {
			if (li_level.currentObject() == li_game.currentObject()) {
				world_manager.markForDelete(li_level.currentObject());
			}
		}
	}

	//Set final score
	final_score = p_s->getValue();

	//Delete player objects
	world_manager.markForDelete(p_t);
	world_manager.markForDelete(p_h);
	world_manager.markForDelete(p_s);
}

void LevelThree::createPlayer() {
	// Create Player.
	p_t = new Tank();

	// Setup heads-up display.
	p_h = new Health();	//Health display
	p_s = new Score();	//Score display
}

void LevelThree::createLevel() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	int x_boundary = world_manager.getBoundary().getHorizontal();
	int y_boundary = world_manager.getBoundary().getVertical();
	int x_view = world_manager.getView().getHorizontal();
	int y_view = world_manager.getView().getVertical();
	int x_mid = world_manager.getBoundary().getHorizontal() / 2;
	int x_left = world_manager.getView().getCorner().getX();
	int x_right = world_manager.getView().getCorner().getX() + world_manager.getView().getHorizontal();
	int offset = 0;
	/*** Build Game World ***/

	//Create Enemies and Obstacles
	//Object *p_m;
	//Start - 0; Barricade

	//0 - 60; Town

	//61 - 90; Fort
	offset = -60;

	//121 - 180; Minefield and bombers
	offset = -120;

	//181 - 240; Bullet tube
	offset = -180;

	//241 - 300; Roadway
	offset = -240;

	//301 - 360; Headquarters
	offset = -300;

	//361 - 420; Last line
	offset = -360;

	//421 - 480; Boss
	offset = -420;
}