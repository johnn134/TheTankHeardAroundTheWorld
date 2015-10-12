/*
* LevelOne.cpp
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
}

void LevelOne::createPlayer() {
	// Create Player.
	p_t = new Tank();

	// Setup heads-up display.
	p_h = new Health();	//Health display
	p_s = new Score();	//Score display
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

	p_m = new Mortar(df::Position(x_right - 4, offset - 26), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 9, offset - 21));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeRock(df::Position(x_right - 6, offset - 31));
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

	p_m = new Mortar(df::Position(x_mid + 3, offset - 50), p_t);
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

	p_m = new SmallRock(df::Position(x_mid + 8, offset - 46));
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

	//241 - 300; No man's land - Middle
	offset = -240;
	p_m = new HoChiMinh(df::Position(x_mid, offset - 30), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//301 - 360; No man's land - Vietnamese side
	offset = -300;

	//361 - 420; Vietnamese front line
	offset = -360;

	//421 - 480; Vietnamese country
	offset = -420;

	//481 - 540; Vietnamese bases
	offset = -480;

	//541 - 600; Ho Chi Minh
	offset = -540;
}