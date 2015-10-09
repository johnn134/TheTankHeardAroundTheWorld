/*
* Helicopter.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyGunShot.h"
#include "Helicopter.h"
#include "SmallExplosion.h"

Helicopter::Helicopter(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("helicopter");
	if (!p_temp_sprite) {
		log_manager.writeLog("Helicopter::Helicopter(): Warning! Sprite '%s' not found", "helicopter");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Helicopter");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);
	setXVelocity(1);

	fire_slowdown = 10;
	fire_countdown = fire_slowdown;
	anim_slowdown = 5;
	anim_countdown = anim_slowdown;

	health = 10;

	flying_right = true;
	first_frame = true;

	//Start helicopter sound
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("chopper-props");
	p_sound->play(true);

	paused = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int Helicopter::eventHandler(const df::Event *p_e) {
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
void Helicopter::setPause(bool new_pause) {
	paused = new_pause;
}

void Helicopter::step() {
	if (!paused) {
		//Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;

		//Sprite countdown
		anim_countdown--;
		if (anim_countdown < 0)
			anim_countdown = 0;

		//Check if needs to turn
		if (getPosition().getX() < 5) {
			flying_right = true;
			setXVelocity(1);
		}
		if (getPosition().getX() > df::WorldManager::getInstance().getBoundary().getHorizontal() - 5) {
			flying_right = false;
			setXVelocity(-1);
		}
	}
}

void Helicopter::fire() {
	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	// Fire Bullet downwards
	EnemyGunShot *p = new EnemyGunShot(df::Position::Position(getPosition().getX(), getPosition().getY() + 2));

	// Play "fire" sound.
}

void Helicopter::hit(const df::EventCollision *p_collision_event) {
	// If Bullet, create explosion and make new Saucer.
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {
		health--;
	}

	if((p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot") || 
		health <= 0) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Delete this object
		df::WorldManager::getInstance().markForDelete(this);
	}
}

//draw frames to match where the player is
void Helicopter::draw(void) {
	//See if change frame
	if (anim_countdown <= 0) {
		anim_countdown = anim_slowdown;
		first_frame = !first_frame;
	}
	
	int dir_frame = 0;
	if (flying_right) {
		if (first_frame)
			dir_frame = 0;
		else
			dir_frame = 1;
	}
	else {
		if (first_frame)
			dir_frame = 2;
		else
			dir_frame = 3;
	}
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}