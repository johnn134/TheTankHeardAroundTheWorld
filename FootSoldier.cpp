/*
* FootSoldier.cpp
*/

//System Headers
#include <math.h>

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
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

	setSolidness(df::Solidness::SOFT);

	//Register interests
	registerInterest(df::STEP_EVENT);

	//Set starting position
	setPosition(p);

	player = new_player;
	boss = NULL;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	paused = false;
}

FootSoldier::FootSoldier(df::Position p, df::Object *new_player, df::Object *new_boss) {
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

	setSolidness(df::Solidness::SOFT);

	//Register interests
	registerInterest(df::STEP_EVENT);

	//Set starting position
	setPosition(p);

	player = new_player;
	boss = new_boss;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	paused = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int FootSoldier::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
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

//Set whether the gameobject is paused or not
void FootSoldier::setPause(bool new_pause) {
	paused = new_pause;
}

void FootSoldier::step() {
	if (!paused) {
		// Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;
	}
}

void FootSoldier::fire() {
	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	//Check if player is in range
	int y_offset = player->getPosition().getY() - getPosition().getY();

	if (y_offset < df::GraphicsManager::getInstance().getVertical() * 3 / 4 && y_offset > 0 &&
		boxIntersectsBox(getWorldBox(this), df::WorldManager::getInstance().getView())) {
		// Fire Bullet towards target.
		df::Position pos;
		if (player->getPosition().getX() > getPosition().getX())
			pos = df::Position::Position(getPosition().getX() + 2, getPosition().getY());
		else
			pos = df::Position::Position(getPosition().getX() - 2, getPosition().getY());
		EnemyGunShot *p = new EnemyGunShot(pos);
		p->setXVelocity((float)(player->getPosition().getX() - pos.getX()) /
			(float)(player->getPosition().getY() - pos.getY()));

		// Play "fire" sound.
	}
}


void FootSoldier::hit(const df::EventCollision *p_collision_event) {
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

		//Tell boss that soldier is dead
		if (boss != NULL) {
			HoChiMinh *p_b = static_cast <HoChiMinh *>(boss);
			p_b->soldierDied(this);
		}

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}

//draw frames to match where the soldier is
void FootSoldier::draw(void) {
	int dir_frame = 0;
	if (player->getPosition().getX() > getPosition().getX())
		dir_frame = 0;
	else
		dir_frame = 1;
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}