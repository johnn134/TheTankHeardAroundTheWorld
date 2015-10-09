/*
* HoChiMinh.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "HoChiMinh.h"

HoChiMinh::HoChiMinh(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "jeep" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("hochiminh");
	if (!p_temp_sprite) {
		log_manager.writeLog("HoChiMinh::HoChiMinh(): Warning! Sprite '%s' not found", "hochiminh");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("HoChiMinh");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);

	player = new_player;
	health = HOCHIMINH_HEALTH;

	soldier1 = NULL;
	soldier2 = NULL;
	soldier3 = NULL;

	fire_slowdown = 5;
	fire_countdown = fire_slowdown;

	in_position = false;
	mouth_open = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int HoChiMinh::eventHandler(const df::Event *p_e) {
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

//Confirm that soldier is dead
void HoChiMinh::soldierDied(df::Object *s) {
	df::LogManager::getInstance().writeLog("soldier died");
	if (s == soldier1) {
		df::LogManager::getInstance().writeLog("1");
		soldier1 = NULL;
	}
	else if (s == soldier2) {
		df::LogManager::getInstance().writeLog("2");
		soldier2 = NULL;
	}
	else if (s == soldier3) {
		df::LogManager::getInstance().writeLog("3");
		soldier3 = NULL;
	}
}

void HoChiMinh::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;

	if (getPosition().getY() >= 13) {
		setYVelocity(0);
		in_position = true;
	}
	if (soldier1 == NULL && soldier2 == NULL && soldier3 == NULL && in_position && !mouth_open) {
		fire();
	}
}

void HoChiMinh::fire() {
	if (fire_countdown > 0)
		return;

	soldier1 = new FootSoldier(df::Position(getPosition().getX(), getPosition().getY() + 15), player, this);
	soldier2 = new FootSoldier(df::Position(getPosition().getX() + 5, getPosition().getY() + 15), player, this);
	soldier3 = new FootSoldier(df::Position(getPosition().getX() - 5, getPosition().getY() + 15), player, this);
	mouth_open = true;
}

void HoChiMinh::hit(const df::EventCollision *p_collision_event) {
	if (mouth_open) {
		if ((p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
			(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {
			health--;
			mouth_open = false;
			if (health <= 0) {
				//Delete this object
				df::WorldManager::getInstance().markForDelete(this);

				df::GameManager::getInstance().setGameOver(true);
			}

			//Reset fire cooldown
			fire_countdown = fire_slowdown;
		}
	}
}

//draw frames to match where the player is
void HoChiMinh::draw() {
	int dir_frame = 0;
	if (mouth_open)
		dir_frame = 1;
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}