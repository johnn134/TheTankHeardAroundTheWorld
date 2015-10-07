/*
* EnemyBombShot.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

//Game Headers
#include "EnemyBombShot.h"
#include "SmallExplosion.h"

EnemyBombShot::EnemyBombShot(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Link to "bullet" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemybombshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("EnemyBombShot::EnemyBombShot(): Warning! Sprite '%s' not found", "enemybombshot");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(BOMB_LIFE);
	}

	//Set other object properties.
	setType("EnemyBombShot");

	setSolidness(df::Solidness::SPECTRAL);

	//Register Interests
	registerInterest(df::STEP_EVENT);

	//Set starting location
	setPosition(p);

	time_to_live = getSprite()->getFrameCount() * BOMB_LIFE;
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyBombShot::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion.
void EnemyBombShot::step() {
	time_to_live--;
	if (time_to_live <= 0){
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		new SmallExplosion(getPosition());
		world_manager.markForDelete(this);
	}
}
