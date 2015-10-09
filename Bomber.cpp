/*
* Bomber.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "utility.h"

//Game Headers
#include "Bomber.h"
#include "EnemyBombShot.h"

Bomber::Bomber(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("bomber");
	if (!p_temp_sprite) {
		log_manager.writeLog("Bomber::Bomber(): Warning! Sprite '%s' not found", "bomber");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}

	setType("Bomber");

	setSolidness(df::Solidness::SPECTRAL);

	//Set starting position
	setPosition(p);
	setYVelocity(1);

	fire_slowdown = 5;
	fire_countdown = fire_slowdown;
	bomb_right = true;

	paused = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int Bomber::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		fire();
		return 1;
	}
	return 0;
}

//Set whether the gameobject is paused or not
void Bomber::setPause(bool new_pause) {
	paused = new_pause;
}

void Bomber::step() {
	if (!paused) {
		// Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;

		bomb_right = !bomb_right;	//Toggle bomb direction with animation
	}
}

void Bomber::fire() {
	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	//Check if bomber is on screen
	if (boxIntersectsBox(getWorldBox(this), df::WorldManager::getInstance().getView())) {
		//Drop bomb
		df::Position pos;
		if (bomb_right) {
			pos = df::Position(getPosition().getX() + 1, getPosition().getY());
		}
		else {
			pos = df::Position(getPosition().getX() - 1, getPosition().getY());
		}
		new EnemyBombShot(pos);

		// Play "fire" sound.
	}
}