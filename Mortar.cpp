/*
* Mortar.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"

//Game Headers
#include "Mortar.h"

Mortar::Mortar(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("mortar");
	if (!p_temp_sprite) {
		log_manager.writeLog("Mortar::Mortar(): Warning! Sprite '%s' not found", "mortar");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Mortar");

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Mortar::eventHandler(const df::Event *p_e) {
	return 0;
}