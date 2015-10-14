/*
* LevelOne.cpp
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
#include "HoChiMinh.h"
#include "Jeep.h"
#include "Landmine.h"
#include "LargeBuilding.h"
#include "LargeRock.h"
#include "LevelOne.h"
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

LevelOne::LevelOne() {
	setType("LevelOne");

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

int LevelOne::eventHandler(const df::Event *p_e) {
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

void LevelOne::draw() {

}

void LevelOne::clearLevel() {
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
	world_manager.markForDelete(p_l);
}

void LevelOne::createPlayer() {
	// Create Player.
	p_t = new Tank();

	// Setup heads-up display.
	p_h = new Health();	//Health display
	p_s = new Score();	//Score display
	p_l = new Lives();	//Lives display
}

void LevelOne::createLevel() {
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
	//Start - 0; American Base
	p_m = new LargeBuilding(df::Position(x_left, y_view - 4));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_right, y_view - 4));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 8, y_view - 16));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 14, y_view - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, y_view - 16));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 14, y_view - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_left + 5, y_view - 24));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_right - 6, y_view - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 12, y_view - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 8, y_view - 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 4, y_view - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 12, y_view - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 8, y_view - 28));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 4, y_view - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//0 - 30; Rocky entrance
	p_m = new MediumRock(df::Position(x_left + 8, offset - 5));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 8, offset - 6));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 16, offset - 15));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallRock(df::Position(x_right - 6, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_left + 12, offset - 12));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_right - 5, offset - 11));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_mid + 4, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallRock(df::Position(x_mid + 12, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 14, offset - 36));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 20, offset - 44), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_left + 14, offset - 46));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 20, offset - 54), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//61 - 90; Rocket guerillas
	offset = -60;
	p_m = new MediumRock(df::Position(x_mid - 2, offset - 6));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 8, offset - 10), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 4, offset - 11), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_left + 9, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 9, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallRock(df::Position(x_mid, offset - 51));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_left + 20, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_right - 20, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 10, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 7, offset - 43), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 10, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 7, offset - 43), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//121 - 180; mortars
	offset = -120;
	p_m = new Mortar(df::Position(x_left + 4, offset - 25), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_left + 9, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_left + 6, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_left + 13, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_right - 4, offset - 27), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 9, offset - 21));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 6, offset - 32));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_right - 13, offset - 26));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_mid, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid - 3, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid + 3, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_mid - 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumRock(df::Position(x_mid + 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallRock(df::Position(x_mid - 8, offset - 46));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallRock(df::Position(x_mid + 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//181 - 240; No man's land - American side
	offset = -180;
	p_m = new BarbWire(df::Position(x_left + 7, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 7, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid - 14, offset - 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid + 14, offset - 31));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 6, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 10, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 14, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 18, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 22, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 4, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 8, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 12, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 16, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 6, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 10, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 14, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 18, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 22, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 4, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 8, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 12, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 16, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_right - 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_left + 4, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_left + 12, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_left + 20, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 20, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 12, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 4, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 4, offset - 41));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 12, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 20, offset - 41));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 20, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 12, offset - 41));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 4, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 14, offset - 44));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_left + 12, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 12, offset - 51));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_right - 20, offset - 54));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//241 - 300; No man's land - Middle
	offset = -240;
	p_m = new BarbWire(df::Position(x_left + 8, offset - 15));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 10, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 10, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Helicopter", df::Position(x_right - 16, offset - 1), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 15, offset - 52), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_left + 10, offset - 65), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_right - 10, offset - 67), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_right - 20, offset - 72), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 5, offset - 85), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//301 - 360; No man's land - Vietnamese side
	offset = -300;
	p_m = new TankTrap(df::Position(x_left + 4, offset - 42));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_right - 4, offset - 42));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid - 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid + 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid - 4, offset - 36));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Landmine(df::Position(x_mid + 4, offset - 36));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 22, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 22, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_left + 4, offset - 49), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 8, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 12, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 16, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_right - 4, offset - 51), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 8, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 12, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 16, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid + 2, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid - 2, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 13, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 17, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 13, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 17, offset - 56), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//361 - 420; Vietnamese front line
	offset = -360;
	p_m = new FootSoldier(df::Position(x_right - 13, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 17, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_right - 16, offset - 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Helicopter", df::Position(x_left + 16, offset - 10), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 4, offset - 27), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 11, offset - 34), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 18, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 4, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 11, offset - 37));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_left + 18, offset - 43));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 3, offset - 47));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 7, offset - 47));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 11, offset - 47));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 15, offset - 47));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 19, offset - 47));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 5, offset - 49));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 9, offset - 49));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 13, offset - 49));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new DragonTooth(df::Position(x_left + 17, offset - 49));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 4, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new SmallBuilding(df::Position(x_right - 4, offset - 52));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//421 - 480; Vietnamese country
	offset = -420;
	p_m = new Egg("Jeep", df::Position(x_left + 13, offset - 15), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_left + 15, offset - 25), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_left + 17, offset - 34), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_right - 13, offset - 17), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_right - 17, offset - 23), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_right - 15, offset - 35), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_mid, offset - 25), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_left + 13, offset - 47), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_right - 13, offset - 43), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumBuilding(df::Position(x_left + 13, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new MediumBuilding(df::Position(x_right - 13, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//481 - 540; Vietnamese bases
	offset = -480;
	p_m = new BarbWire(df::Position(x_left + 14, offset - 5));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 14, offset - 10));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_mid, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_left + 18, offset - 8), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_right - 18, offset - 13), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 10, offset - 8), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_right - 10, offset - 13), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_left + 10, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_right - 10, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 5, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 15, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 25, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 35, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 45, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_left + 55, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//541 - 600; Ho Chi Minh
	offset = -540;
	p_m = new HoChiMinh(df::Position(x_mid, offset - 10), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);
}