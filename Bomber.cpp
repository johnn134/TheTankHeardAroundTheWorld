/*
* Bomber.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"

//Game Headers
#include "Bomber.h"

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
		setSpriteSlowdown(0);
	}

	setType("Bomber");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bomber::eventHandler(const df::Event *p_e) {
	return 0;
}