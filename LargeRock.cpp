/*
* LargeRock.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "LargeRock.h"
#include "SmallExplosion.h"

LargeRock::LargeRock(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "largerock" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("largerock");
	if (!p_temp_sprite) {
		log_manager.writeLog("LargeRock::LargeRock(): Warning! Sprite '%s' not found", "largerock");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("LargeRock");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);

	health = 25;
	hit_slowdown = 5;
	hit_countdown = hit_slowdown;
	was_hit = false;
	has_flashed = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int LargeRock::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void LargeRock::step() {
	if (was_hit) {
		hit_countdown--;
		if (hit_countdown < 0) {
			hit_countdown = 0;
			was_hit = false;
		}
	}
}

void LargeRock::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {
		if (!was_hit) {
			health--;
			was_hit = true;
			has_flashed = false;
			hit_countdown = hit_slowdown;
		}
	}

	// If PlayerCannonShot or Player, create explosion and delete rock
	if ((p_collision_event->getObject1()->getType() == "Tank") ||
		(p_collision_event->getObject2()->getType() == "Tank") ||
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot") ||
		health <= 0) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}

//Draw frames to match where the rock is
void LargeRock::draw(void) {
	int dir_frame = 0;
	if (was_hit && !has_flashed) {
		dir_frame = 1;
		has_flashed = true;
	}
	else
		dir_frame = 0;
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}