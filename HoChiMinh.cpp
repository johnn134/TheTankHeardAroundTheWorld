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
#include "EventLevelComplete.h"
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

	//Register interests
	registerInterest(df::STEP_EVENT);
	registerInterest(FOOT_SOLDIER_DEATH_EVENT);

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

	if (p_e->getType() == FOOT_SOLDIER_DEATH_EVENT) {
		const EventFootSoldierDeath *p_death_event = dynamic_cast <EventFootSoldierDeath const *> (p_e);
		soldierDied(p_death_event);
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
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

	soldier1 = new FootSoldier(df::Position(getPosition().getX(), getPosition().getY() + 15), player);
	soldier2 = new FootSoldier(df::Position(getPosition().getX() + 5, getPosition().getY() + 15), player);
	soldier3 = new FootSoldier(df::Position(getPosition().getX() - 5, getPosition().getY() + 15), player);
	mouth_open = true;
}

void HoChiMinh::hit(const df::EventCollision *p_collision_event) {
	if (mouth_open) {
		if ((p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
			(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {
			health--;
			mouth_open = false;
			if (health <= 0) {
				//Return to Level Select
				EventLevelComplete ev;
				df::WorldManager::getInstance().onEvent(&ev);
			}

			//Reset fire cooldown
			fire_countdown = fire_slowdown;
		}
	}
}

void HoChiMinh::soldierDied(const EventFootSoldierDeath *p_death_event) {
	if (soldier1 == p_death_event->getSoldier()) {
		soldier1 = NULL;
	}
	else if (soldier2 == p_death_event->getSoldier()) {
		soldier2 = NULL;
	}
	else if (soldier3 == p_death_event->getSoldier()) {
		soldier3 = NULL;
	}
}

//draw frames to match where the player is
void HoChiMinh::draw() {
	int dir_frame = 0;
	if (mouth_open)
		dir_frame = 1;
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}