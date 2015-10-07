/*
* RocketSoldier.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyRocketShot.h"
#include "RocketSoldier.h"
#include "SmallExplosion.h"

RocketSoldier::RocketSoldier(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("rocketsoldier");
	if (!p_temp_sprite) {
		log_manager.writeLog("RocketSoldier::RocketSoldier(): Warning! Sprite '%s' not found", "rocketsoldier");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("RocketSoldier");

	//Register interests
	registerInterest(df::STEP_EVENT);

	//Set starting position
	setPosition(p);

	//Set to move down constantly
	setYVelocity(0.10f);

	player = new_player;
	fire_slowdown = 60;
	fire_countdown = fire_slowdown;
	rocketInTube = true;
}

// Handle event.
// Return 0 if ignored, else 1.
int RocketSoldier::eventHandler(const df::Event *p_e) {
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

void RocketSoldier::fire() {
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;

	//See if rocket should be placed in tube
	if (fire_countdown < fire_slowdown / 3)
		rocketInTube = true;

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
			pos = df::Position::Position(getPosition().getX() + 3, getPosition().getY());
		else
			pos = df::Position::Position(getPosition().getX() - 3, getPosition().getY());
		EnemyRocketShot *p = new EnemyRocketShot(pos);
		p->setXVelocity((float)(player->getPosition().getX() - pos.getX()) /
						(float)(player->getPosition().getY() - pos.getY()) * 0.5f);

		rocketInTube = false;

		// Play "fire" sound.
	}
}


void RocketSoldier::hit(const df::EventCollision *p_collision_event) {
	// If Bullet, create explosion and make new Saucer.
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}

//draw frames to match where the player is
void RocketSoldier::draw(void) {
	int dir_frame = 0;
	if (player->getPosition().getX() < getPosition().getX()) {
		if (rocketInTube)
			dir_frame = 0;
		else
			dir_frame = 1;
	}
	else {
		if (rocketInTube)
			dir_frame = 2;
		else
			dir_frame = 3;
	}
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}