/*
* Trench.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"

//Game Headers
#include "Trench.h"

Trench::Trench(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "trench" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("trench");
	if (!p_temp_sprite) {
		log_manager.writeLog("Trench::Trench(): Warning! Sprite '%s' not found", "trench");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Trench");

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Trench::eventHandler(const df::Event *p_e) {
	return 0;
}