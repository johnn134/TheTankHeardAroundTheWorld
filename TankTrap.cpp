/*
* TankTrap.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"

//Game Headers
#include "TankTrap.h"

TankTrap::TankTrap(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "tanktrap" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("tanktrap");
	if (!p_temp_sprite) {
		log_manager.writeLog("TankTrap::TankTrap(): Warning! Sprite '%s' not found", "tanktrap");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("TankTrap");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int TankTrap::eventHandler(const df::Event *p_e) {
	return 0;
}