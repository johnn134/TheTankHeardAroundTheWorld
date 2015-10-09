/*
* GameStart.cpp
*/

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

// Game includes.
#include "BarbWire.h"
#include "Bomber.h"
#include "DragonTooth.h"
#include "EnemyTank.h"
#include "FootSoldier.h"
#include "GameStart.h"
#include "Health.h"
#include "Helicopter.h"
#include "HoChiMinh.h"
#include "Jeep.h"
#include "Landmine.h"
#include "LargeBuilding.h"
#include "LargeRock.h"
#include "Lives.h"
#include "MediumBuilding.h"
#include "MediumRock.h"
#include "Mortar.h"
#include "PowerUp.h"
#include "RocketSoldier.h"
#include "Score.h"
#include "SmallBuilding.h"
#include "SmallRock.h"
#include "Tank.h"
#include "TankTrap.h"

GameStart::GameStart() {

	setType("GameStart");

	// Put in center of screen.
	setLocation(df::CENTER_CENTER);

	// Register for "keyboard" event.
	registerInterest(df::KEYBOARD_EVENT);
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {
	df::GameManager &game_manager = df::GameManager::getInstance();

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			switch (p_keyboard_event->getKey()) {
			case df::Keyboard::P: 			// play
				start();
				break;
			case df::Keyboard::Q:			// quit
				game_manager.setGameOver();
				break;
			default:
				break;
		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

void GameStart::start() {
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
	// Create Player.
	Tank *p_t = new Tank();
	new Score();
	
	//Create Enemies and Obstacles
	Object *p_m;
	//Start - 0; American Base
	p_m = new LargeBuilding(df::Position(x_left, y_view - 4));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeBuilding(df::Position(x_right, y_view - 4));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_left + 8, y_view - 16));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_left + 14, y_view - 20));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_right - 8, y_view - 16));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_right - 14, y_view - 20));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_left + 5, y_view - 24));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_right - 6, y_view - 25));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_left + 12, y_view - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_left + 8, y_view - 28));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_left + 4, y_view - 30));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_right - 12, y_view - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_right - 8, y_view - 28));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Landmine(df::Position(x_right - 4, y_view - 30));
	p_m->setYVelocity(SCROLL_SPEED);

	//0 - 30; Rocky entrance
	p_m = new MediumRock(df::Position(x_left + 8, offset - 5));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 8, offset - 6));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 16, offset - 15));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new SmallRock(df::Position(x_right - 6, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_left + 12, offset - 12));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_right - 5, offset - 11));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_mid + 4, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new SmallRock(df::Position(x_mid + 12, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 14, offset - 36));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_right - 20, offset - 44), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_left + 14, offset - 46));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_left + 20, offset - 54), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	//61 - 90; Rocket guerillas
	offset = -60;
	p_m = new MediumRock(df::Position(x_mid - 2, offset - 6));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_mid - 8, offset - 10), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_mid + 4, offset - 11), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_left + 9, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 9, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new SmallRock(df::Position(x_mid, offset - 51));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new RocketSoldier(df::Position(x_left + 20, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new RocketSoldier(df::Position(x_right - 20, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_left + 10, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_left + 7, offset - 43), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_right - 10, offset - 45), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new FootSoldier(df::Position(x_right - 7, offset - 43), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	//121 - 180; mortars
	offset = -120;
	p_m = new Mortar(df::Position(x_left + 4, offset - 25), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_left + 9, offset - 20));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_left + 6, offset - 30));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_left + 13, offset - 25));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Mortar(df::Position(x_right - 4, offset - 26), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 9, offset - 21));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_right - 6, offset - 31));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_right - 13, offset - 26));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new LargeRock(df::Position(x_mid, offset - 55));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Mortar(df::Position(x_mid - 3, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new Mortar(df::Position(x_mid + 3, offset - 50), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_mid - 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new MediumRock(df::Position(x_mid + 10, offset - 50));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new SmallRock(df::Position(x_mid - 8, offset - 46));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new SmallRock(df::Position(x_mid + 8, offset - 46));
	p_m->setYVelocity(SCROLL_SPEED);

	//181 - 240; No man's land - American side
	offset = -180;
	p_m = new BarbWire(df::Position(x_left + 7, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_mid, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_right - 7, offset - 29));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_mid - 14, offset - 31));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new BarbWire(df::Position(x_mid + 14, offset - 31));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 6, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 10, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 14, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 18, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 22, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 4, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 8, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 12, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 16, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_left + 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 2, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 6, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 10, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 14, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 18, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 22, offset - 33));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 4, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 8, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 12, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 16, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	p_m = new DragonTooth(df::Position(x_right - 20, offset - 35));
	p_m->setYVelocity(SCROLL_SPEED);

	//241 - 300; No man's land - Middle
	offset = -240;
	p_m = new HoChiMinh(df::Position(x_mid, offset - 30), p_t);
	p_m->setYVelocity(SCROLL_SPEED);

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


	// Setup heads-up display.
	new Health();	//Health display

	// When game starts, destroy this object.
	world_manager.markForDelete(this);
}

// Override default draw so as not to display "value".
void GameStart::draw() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::Position mid_pos = df::Position(world_manager.getView().getCorner().getX() + 
										world_manager.getView().getHorizontal() / 2,
										world_manager.getView().getCorner().getY() +
										world_manager.getView().getVertical() / 2);
	graphics_manager.drawString(mid_pos, "The Tank Heard Around The World", 
								df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);
	graphics_manager.drawString(df::Position(mid_pos.getX(), mid_pos.getY() + 2), "WASD to move, mouse click to fire machinegun, space to fire cannon",
								df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);
	graphics_manager.drawString(df::Position(mid_pos.getX(), mid_pos.getY() + 4), "Press p to play, q to quit",
								df::Justification::CENTER_JUSTIFIED, df::Color::BLACK);
}
