/*
* LevelTwo.cpp
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
#include "LevelTwo.h"
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
#include "Egg.h"

LevelTwo::LevelTwo() {
	setType("LevelTwo");

	setLocation(df::CENTER_CENTER);

	//Register interest for 'levelfailed' event
	registerInterest(LEVELFAILED_EVENT);

	//Register interest for 'levelcomplete' event
	registerInterest(LEVELCOMPLETE_EVENT);

	final_score = 0;
	p_t = NULL;
	p_h = NULL;
	p_s = NULL;
	p_l = NULL;

	createPlayer();
	createLevel();
}

int LevelTwo::eventHandler(const df::Event *p_e) {
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

void LevelTwo::draw() {

}

void LevelTwo::clearLevel() {
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

void LevelTwo::createPlayer() {
	// Create Player.
	p_t = new Tank();

	// Setup heads-up display.
	p_h = new Health();	//Health display
	p_s = new Score();	//Score display
	p_l = new Lives(); //lives display
}

void LevelTwo::createLevel() {
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

	//0 - 30; Barbed Welcome Mat
	p_m = new BarbWire(df::Position(x_left + 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 23, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid, offset-2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 5, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 5, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 10, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 10, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 15, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 15, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 20, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 20, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 25, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 25, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 30, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 30, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//51-110 second line with mortars
	offset = -50;
	p_m = new BarbWire(df::Position(x_left + 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 23, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 5, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 5, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 10, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 10, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 15, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 15, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 20, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 20, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 25, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 25, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid + 30, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new TankTrap(df::Position(x_mid - 30, offset - 2));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid - 21, offset - 5), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid + 21, offset - 5), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//111 - 180; Enter the city
	offset = -110;
	p_m = new BarbWire(df::Position(x_left + 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_left + 23, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_mid - 15, offset - 6));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 2, offset - 6), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 10, offset - 6), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);
	p_m = new FootSoldier(df::Position(x_mid + 18, offset - 6), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new LargeBuilding(df::Position(x_mid + 15, offset - 40));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 5, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 13, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 23, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset-35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset-35));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//181 - 330 Jeep Showdown
	offset = -180;

	p_m = new MediumBuilding(df::Position(x_mid, offset));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	for (int i = 0; i < 16; i++){
		p_m = new MediumBuilding(df::Position(x_mid, offset - i * 9));
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);
	}

	p_m = new Egg("Jeep", df::Position(x_mid - 20, offset - 5), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 20, offset - 15), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 16, offset - 28), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 16, offset - 28), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 16, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 16, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 24, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 24, offset - 40), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 22, offset - 55), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 16, offset - 70), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 17, offset - 85), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 20, offset - 100), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 20, offset - 110), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 25, offset - 130), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid - 20, offset - 135), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 20, offset - 135), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid - 24, offset - 142), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid + 24, offset - 142), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);
	p_m = new RocketSoldier(df::Position(x_mid - 16, offset - 142), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid + 16, offset - 142), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//331 - 510; the street
	offset = -330;
	for (int j = 0; j < 20; j++){
		p_m = new MediumBuilding(df::Position(x_left + 5, offset - j * 9));
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);

		if (j % 8 == 0){
			p_m = new Mortar(df::Position(x_left + 5, offset - (j * 9) - 4), p_t);
			p_m->setYVelocity(SCROLL_SPEED);
			level_objects.insert(p_m);
		}

		if (j % 4 == 0){
			p_m = new FootSoldier(df::Position(x_left + 11, offset - (j * 9) - 4), p_t);
			p_m->setYVelocity(SCROLL_SPEED);
			level_objects.insert(p_m);
		}
	}

	for (int k = 0; k < 20; k++){
		p_m = new MediumBuilding(df::Position(x_right - 6, offset - k * 9));
		p_m->setYVelocity(SCROLL_SPEED);
		level_objects.insert(p_m);

		if (k % 5 == 0){
			p_m = new RocketSoldier(df::Position(x_right - 11, offset - (k * 9) - 4), p_t);
			p_m->setYVelocity(SCROLL_SPEED);
			level_objects.insert(p_m);
		}
	}

	p_m = new Egg("Jeep", df::Position(x_mid + 15, offset - 30), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Jeep", df::Position(x_mid + 15, offset - 30), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 5, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 5, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 15, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 15, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid, offset - 60), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_mid, offset - 70), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_mid - 18, offset - 90), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("EnemyTank", df::Position(x_mid + 18, offset - 140), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 15, offset - 105), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid + 15, offset - 105), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid - 20, offset - 165), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid + 20, offset - 165), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Egg("Bomber", df::Position(x_mid, offset - 160), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//511 - 550; Last line
	offset = -510;

	p_m = new BarbWire(df::Position(x_right - 8, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_right - 24, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new BarbWire(df::Position(x_mid, offset - 45));
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid + 5, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid - 5, offset - 48), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid + 10, offset - 49), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new FootSoldier(df::Position(x_mid - 10, offset - 49), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new Mortar(df::Position(x_mid + 15, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	p_m = new RocketSoldier(df::Position(x_mid - 15, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);
	level_objects.insert(p_m);

	//Boss3
}