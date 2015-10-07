/*
* EnemyRocketShot.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

//Game Headers
#include "EnemyRocketShot.h"
#include "SmallExplosion.h"

EnemyRocketShot::EnemyRocketShot(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Link to "bullet" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemyrocketshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("EnemyGunShot::EnemyGunShot(): Warning! Sprite '%s' not found", "enemyrocketshot");
	}
	else {
		setSprite(p_temp_sprite);
	}

	//Set other object properties.
	setType("EnemyRocketShot");

	setSolidness(df::Solidness::SOFT);

	//Set starting location
	setPosition(p);

	setYVelocity(0.5); // Move 1 space down every game loop.
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyRocketShot::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If Bullet moves outside world, mark self for deletion.
void EnemyRocketShot::out() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion.
void EnemyRocketShot::hit(const df::EventCollision *p_collision_event) {
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	//Create explosion
	SmallExplosion *p_explosion = new SmallExplosion(getPosition());

	world_manager.markForDelete(this);
}
