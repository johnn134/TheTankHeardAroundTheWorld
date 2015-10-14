/*
* LevelThree.cpp
*/

//Dragonfly Headers
#include "WorldManager.h"

//Game includes.
#include "BarbWire.h"
#include "Bomber.h"
#include "DragonTooth.h"
#include "Egg.h"
#include "EnemyTank.h"
#include "EventLevelComplete.h"
#include "EventLevelFailed.h"
#include "EventLevelHandled.h"
#include "FootSoldier.h"
#include "Health.h"
#include "Helicopter.h"
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
#include "Nixon.h"
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
	Object *p_m;
	//Start - 0; Barricade
	p_m = new BarbWire(df::Position(x_mid + 7, 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid - 7, 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 2, 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 2, 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 6, 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 6, 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_left + 4, 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_left + 8, 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 4, 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 8, 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 4, 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 8, 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 4, 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 8, 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//0 - 60; Town
	p_m = new SmallBuilding(df::Position(x_left + 4, offset - 7));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_mid + 5, offset - 7));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 4, offset - 7));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 4, offset - 27));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 4, offset - 24), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_mid + 5, offset - 27));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 4, offset - 27));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 12, offset - 27), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 4, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 8, offset - 43));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_mid - 4, offset - 38));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid, offset - 34), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 6, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 10, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//61 - 90; Fort
	offset = -60;
	p_m = new LargeBuilding(df::Position(x_right - 18, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumBuilding(df::Position(x_right - 22, offset - 18));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_left + 16, offset - 27), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumBuilding(df::Position(x_right - 11, offset - 18));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 18, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_left + 16, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 6, offset - 58));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 6, offset - 58));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//121 - 180; Minefield and bombers
	offset = -120;
	p_m = new Landmine(df::Position(x_left + 3, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 7, offset - 4));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 3, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 7, offset - 4));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid - 10, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid + 10, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid + 5, offset - 42), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 5, offset - 52), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 3, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 7, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 11, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 15, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 19, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_left - 20, offset - 60), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_left - 10, offset - 62), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid, offset - 75), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 5, offset - 78), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid + 5, offset - 72), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 8, offset - 59));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset - 59));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//181 - 240; Bullet tube
	offset = -180;
	for (int i = 0; i < 6; i++) {
		p_m = new SmallBuilding(df::Position(x_left + 5, offset - 10 * i));
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);

		p_m = new SmallBuilding(df::Position(x_right - 5, offset - 10 * i));
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);

		p_m = new FootSoldier(df::Position(x_left + 10, offset - 10 * i), p_t);
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);

		p_m = new FootSoldier(df::Position(x_right - 10, offset - 10 * i), p_t);
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);
	}

	//241 - 300; Roadway

	//301 - 360; Headquarters

	//361 - 420; Last line
	offset = -240;
	p_m = new BarbWire(df::Position(x_left + 8, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 8, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 25, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 25, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 25, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_left + 16, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 35, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 35, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 35, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//421 - 480; Boss
	offset = -300;
	p_m = new Nixon(df::Position(x_mid, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);
}