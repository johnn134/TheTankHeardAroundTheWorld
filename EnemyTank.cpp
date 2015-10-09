/*
* EnemyTank.cpp
*/

//System Headers
#include <stdlib.h>

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyCannonShot.h"
#include "EnemyTank.h"
#include "SmallExplosion.h"

EnemyTank::EnemyTank(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemytank");
	if (!p_temp_sprite) {
		log_manager.writeLog("EnemyTank::EnemyTank(): Warning! Sprite '%s' not found", "enemytank");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("EnemyTank");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);

	player = new_player;
	fire_slowdown = 60;
	fire_countdown = fire_slowdown;
	move_slowdown = 5;
	move_countdown = move_slowdown;
	
	paused = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyTank::eventHandler(const df::Event *p_e) {
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
void EnemyTank::setPause(bool new_pause) {
	paused = new_pause;
}

void EnemyTank::step() {
	if (!paused) {
		// Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;

		// Move countdown.
		move_countdown--;
		if (move_countdown < 0)
			move_countdown = 0;

		//Move towards player
		if (getPosition().getX() < player->getPosition().getX()) {
			move(1);
		}
		else if (getPosition().getX() > player->getPosition().getX()) {
			move(-1);
		}
		else {
			setXVelocity(0);
		}
	}
}

void EnemyTank::fire() {

	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	//Check if player is in range
	int y_offset = player->getPosition().getY() - getPosition().getY();
	int x_offset = player->getPosition().getX() - getPosition().getX();

	if (y_offset < df::GraphicsManager::getInstance().getVertical() * 3 / 4 && y_offset > 0 &&
		boxIntersectsBox(getWorldBox(this), df::WorldManager::getInstance().getView()) &&
		abs(x_offset) < 4) {
		// Fire Cannon
		EnemyCannonShot *p = new EnemyCannonShot(df::Position(getPosition().getX(), getPosition().getY() + 6));

		// Play "cannonFire" sound.
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("cannon-shot");
		p_sound->play();
	}
}


void EnemyTank::hit(const df::EventCollision *p_collision_event) {
	// If PlayerTank or PlayerCannonShot, create explosion and delete Tank
	if ((p_collision_event->getObject1()->getType() == "Tank") ||
		(p_collision_event->getObject2()->getType() == "Tank") || 
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}

// Move up or down.
void EnemyTank::move(int dx) {

	// See if time to move.
	if (move_countdown > 0)
		return;

	//Reset countdown
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Position new_pos(getPosition().getX() + dx, getPosition().getY());
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	if ((new_pos.getX() > 3) &&
		(new_pos.getX() < world_manager.getView().getHorizontal() - 3))
		world_manager.moveObject(this, new_pos);
}