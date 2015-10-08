/*
* DragonTooth.cpp
*/

//Dragonfly Headers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "DragonTooth.h"
#include "SmallExplosion.h"

DragonTooth::DragonTooth(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "dragontooth" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("dragontooth");
	if (!p_temp_sprite) {
		log_manager.writeLog("DragonTooth::DragonTooth(): Warning! Sprite '%s' not found", "dragontooth");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("DragonTooth");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int DragonTooth::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void DragonTooth::hit(const df::EventCollision *p_collision_event) {
	// If PlayerCannonShot or Player, create explosion and delete building
	if ((p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}