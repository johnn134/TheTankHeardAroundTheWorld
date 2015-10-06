/*
* SmallBuilding.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"

//Game Headers
#include "SmallBuilding.h"

SmallBuilding::SmallBuilding(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("smallbuilding");
	if (!p_temp_sprite) {
		log_manager.writeLog("SmallBuilding::SmallBuilding(): Warning! Sprite '%s' not found", "smallbuilding");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("SmallBuilding");

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int SmallBuilding::eventHandler(const df::Event *p_e) {
	return 0;
}