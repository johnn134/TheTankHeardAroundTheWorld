/*
* Landmine.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "Landmine.h"
#include "SmallExplosion.h"

Landmine::Landmine(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("landmine");
	if (!p_temp_sprite) {
		log_manager.writeLog("Landmine::Landmine(): Warning! Sprite '%s' not found", "landmine");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}

	setType("Landmine");

	//Set starting position
	setPosition(p);
	setYVelocity(0.1f);
}

// Handle event.
// Return 0 if ignored, else 1.
int Landmine::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Landmine::hit(const df::EventCollision *p_collision_event) {
	// If PlayerGunShot or PlayerCannonShot, create explosion and delete soldier
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject1()->getType() == "Tank") ||
		(p_collision_event->getObject2()->getType() == "Tank")) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}