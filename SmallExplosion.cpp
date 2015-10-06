/*
* SmallExplosion.h
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "SmallExplosion.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

SmallExplosion::SmallExplosion(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("smallexplosion");
	if (!p_temp_sprite) {
		log_manager.writeLog("SmallExplosion::SmallExplosion(): Warning! Sprite '%s' not found", "smallexplosion");
	}
	else {
		setSprite(p_temp_sprite);
	}

	setType("SmallExplosion");

	setSolidness(df::SPECTRAL);

	//Register Interests
	registerInterest(df::STEP_EVENT);

	//Set starting position
	setPosition(p);

	time_to_live = getSprite()->getFrameCount();
}

// Handle event.
// Return 0 if ignored, else 1.
int SmallExplosion::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down until explosion finished.
void SmallExplosion::step() {
	time_to_live--;
	if (time_to_live <= 0){
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}
