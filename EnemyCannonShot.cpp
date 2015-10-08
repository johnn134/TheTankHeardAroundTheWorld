/*
* EnemyCannonShot.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

//Game Headers
#include "EnemyCannonShot.h"
#include "SmallExplosion.h"

EnemyCannonShot::EnemyCannonShot(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Link to "enemycannonshot" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemycannonshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("EnemyCannonShot::EnemyCannonShot(): Warning! Sprite '%s' not found", "enemycannonshot");
	}
	else {
		setSprite(p_temp_sprite);
	}

	//Set other object properties.
	setType("EnemyCannonShot");

	setSolidness(df::Solidness::SOFT);

	//Set starting location
	setPosition(p);

	setYVelocity(2); // Move 2 spaces down every game loop.
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyCannonShot::eventHandler(const df::Event *p_e) {

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

// If cannon shot moves outside world, mark self for deletion.
void EnemyCannonShot::out() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

// If cannon shot hits anything, delete it
void EnemyCannonShot::hit(const df::EventCollision *p_collision_event) {
	if (p_collision_event->getObject1()->getType() != "EnemyGunShot" &&
		p_collision_event->getObject2()->getType() != "EnemyGunShot" &&
		p_collision_event->getObject1()->getType() != "EnemyRocketShot" &&
		p_collision_event->getObject2()->getType() != "EnemyRocketShot" &&
		p_collision_event->getObject1()->getType() != "BarbWire" &&
		p_collision_event->getObject2()->getType() != "BarbWire" &&
		p_collision_event->getObject1()->getType() != "FootSoldier" &&
		p_collision_event->getObject2()->getType() != "FootSoldier" &&
		p_collision_event->getObject1()->getType() != "RocketSoldier" &&
		p_collision_event->getObject2()->getType() != "RocketSoldier" &&
		p_collision_event->getObject1()->getType() != "Helicopter" &&
		p_collision_event->getObject2()->getType() != "Helicopter" &&
		p_collision_event->getObject1()->getType() != "PlayerGunShot" &&
		p_collision_event->getObject2()->getType() != "PlayerGunShot") {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		new SmallExplosion(getPosition());
		world_manager.markForDelete(this);
	}
}
