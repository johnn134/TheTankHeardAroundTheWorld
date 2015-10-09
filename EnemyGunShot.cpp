/*
* EnemyGunShot.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

//Game Headers
#include "EnemyGunShot.h"

EnemyGunShot::EnemyGunShot(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Link to "enemygunshot" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemygunshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("EnemyGunShot::EnemyGunShot(): Warning! Sprite '%s' not found", "enemygunshot");
	}
	else {
		setSprite(p_temp_sprite);
	}

	//Set other object properties.
	setType("EnemyGunShot");

	setSolidness(df::Solidness::SOFT);

	//Set starting location
	setPosition(p);

	setYVelocity(1); // Move 1 space down every game loop.
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyGunShot::eventHandler(const df::Event *p_e) {

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
void EnemyGunShot::out() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

// If gun shot hits anything, delete it
void EnemyGunShot::hit(const df::EventCollision *p_collision_event) {
	if (p_collision_event->getObject1()->getType() != "EnemyCannonShot" &&
		p_collision_event->getObject2()->getType() != "EnemyCannonShot" &&
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
		p_collision_event->getObject2()->getType() != "PlayerGunShot" &&
		p_collision_event->getObject1()->getType() != "PlayerCannonShot" &&
		p_collision_event->getObject2()->getType() != "PlayerCannonShot" &&
		p_collision_event->getObject1()->getType() != "Powerup" &&
		p_collision_event->getObject2()->getType() != "Powerup") {
		df::WorldManager &world_manager = df::WorldManager::getInstance();

		//Play gun impact sound
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("gun-impact");
		p_sound->play();

		world_manager.markForDelete(this);
	}
}
