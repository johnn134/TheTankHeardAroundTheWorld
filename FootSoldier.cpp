/*
* FootSoldier.cpp
*/

//System Headers
#include <math.h>

//Dragonfly Headers
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyGunShot.h"
#include "FootSoldier.h"
#include "SmallExplosion.h"

FootSoldier::FootSoldier(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("footsoldier");
	if (!p_temp_sprite) {
		log_manager.writeLog("FootSoldier::FootSoldier(): Warning! Sprite '%s' not found", "footsoldier");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("FootSoldier");

	//Register interests
	registerInterest(df::STEP_EVENT);

	//Set starting position
	setPosition(p);

	//Set to move down constantly
	setYVelocity(0.10f);

	player = new_player;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
}

// Handle event.
// Return 0 if ignored, else 1.
int FootSoldier::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		fire();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void FootSoldier::fire() {
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
	
	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	//Check if player is in range
	int y_offset = player->getPosition().getY() - getPosition().getY();

	if (y_offset < 24 && y_offset > 0) {
		// Fire Bullet towards target.
		EnemyGunShot *p = new EnemyGunShot(df::Position::Position(getPosition().getX(), getPosition().getY() + 3));
		p->setXVelocity((float)(player->getPosition().getX() - getPosition().getX()) /
						(float)(player->getPosition().getY() - getPosition().getY()));

		// Play "fire" sound.
	}
}


void FootSoldier::hit(const df::EventCollision *p_collision_event) {
	// If Bullet, create explosion and make new Saucer.
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}