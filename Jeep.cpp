/*
* Jeep.cpp
*/

//System Headers
#include <stdlib.h>

//Dragonfly Headers
#include "EventStep.h"
#include "EventView.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyGunShot.h"
#include "Jeep.h"
#include "Score.h"
#include "SmallExplosion.h"
#include "EventFootSoldierDeath.h"

Jeep::Jeep(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "jeep" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("jeep");
	if (!p_temp_sprite) {
		log_manager.writeLog("Jeep::Jeep(): Warning! Sprite '%s' not found", "jeep");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Jeep");

	setSolidness(df::Solidness::SOFT);

	registerInterest(df::OUT_EVENT);

	//Set starting position
	setPosition(p);

	player = new_player;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	anim_slowdown = ANIMATION_DELAY;
	anim_countdown = anim_slowdown;
	curFrame = 0;
	health = HEALTH;
	hit_slowdown = 5;
	hit_countdown = hit_slowdown;
	was_hit = false;
	has_flashed = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int Jeep::eventHandler(const df::Event *p_e) {
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

	if (p_e->getType() == df::OUT_EVENT){
		if (getPosition().getY() > 10){
			// Create "footsoldierdeath" event and send to interested Objects.
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			EventFootSoldierDeath death(this);
			world_manager.onEvent(&death);

			//Delete this object
			world_manager.markForDelete(this);
		}

		return 1;
	}
	return 0;
}

void Jeep::step() {
	// Hit countdown
	if (was_hit) {
		hit_countdown--;
		if (hit_countdown < 0) {
			hit_countdown = 0;
			was_hit = false;
		}
	}

	//Firing animation countdown
	anim_countdown--;
	if (anim_countdown < 0)
		anim_countdown = 0;

	//See if firing is finished
	if (anim_countdown <= 0) {
		curFrame++;
		if (curFrame > 3)
			curFrame = 0;
		anim_countdown = anim_slowdown;
	}

	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

void Jeep::fire() {
	// See if time to fire.
	if (fire_countdown > 0)
		return;

	//Reset countdown
	fire_countdown = fire_slowdown;

	//Check if player is in range
	int y_offset = player->getPosition().getY() - getPosition().getY();
	int x_offset = player->getPosition().getX() - getPosition().getX();

	if (abs(y_offset) < df::GraphicsManager::getInstance().getVertical() * 3 / 4 &&
		boxIntersectsBox(getWorldBox(this), df::WorldManager::getInstance().getView())) {
		// Fire Gun
		df::Position pos;
		if (getPosition().getX() < player->getPosition().getX()) {
			pos = df::Position(getPosition().getX() + 4, getPosition().getY());
		}
		else {
			pos = df::Position(getPosition().getX() - 4, getPosition().getY());
		}
		EnemyGunShot *p = new EnemyGunShot(pos);
		p->setXVelocity((float)(player->getPosition().getX() - pos.getX()) /
						(float)(player->getPosition().getY() - pos.getY()));

		// Play "gunshot" sound.
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("gun-shot");
		p_sound->play();
	}
}


void Jeep::hit(const df::EventCollision *p_collision_event) {
	//If PlayerGunShot damage jeep
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {
		if (!was_hit) {
			health--;
			was_hit = true;
			has_flashed = false;
			hit_countdown = hit_slowdown;
		}
	}

	// If PlayerTank or PlayerCannonShot, create explosion and delete jeep
	if ((p_collision_event->getObject1()->getType() == "Tank") ||
		(p_collision_event->getObject2()->getType() == "Tank") ||
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot") ||
		health <= 0) {

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		// Create "footsoldierdeath" event and send to interested Objects.
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		EventFootSoldierDeath death(this);
		world_manager.onEvent(&death);

		//Send Points for deletion
		df::EventView ev(SCORE_STRING, JEEP_POINTS, true);
		world_manager.onEvent(&ev);

		//Delete this object
		world_manager.markForDelete(this);
	}
}

//draw frames to match where the rock is
void Jeep::draw(void) {
	int dir_frame = 0;
	if (was_hit && !has_flashed) {
		dir_frame = 4;
		has_flashed = true;
	}
	else {
		dir_frame = curFrame;
	}
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}