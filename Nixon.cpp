/*
* Nixon.cpp
*/

//Dragonfly Headers
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game Headers
#include "EventFootSoldierDeath.h"
#include "EventLevelComplete.h"
#include "FootSoldier.h"
#include "LevelOne.h"
#include "Nixon.h"
#include "NixonPowerCell.h"
#include "Mortar.h"
#include "Score.h"

Nixon::Nixon(df::Position p) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "jeep" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("nixon");
	if (!p_temp_sprite) {
		log_manager.writeLog("Nixon::Nixon(): Warning! Sprite '%s' not found", "nixon");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Nixon");

	setSolidness(df::Solidness::SOFT);

	//Register interests
	registerInterest(df::STEP_EVENT);
	registerInterest(FOOT_SOLDIER_DEATH_EVENT);

	//Set starting position
	setPosition(p);
	health = NIXON_HEALTH;

	df::WorldManager &world_manager = df::WorldManager::getInstance();
	int x_left = world_manager.getView().getCorner().getX();
	int x_right = world_manager.getView().getCorner().getX() + world_manager.getView().getHorizontal();

	tank1 = new NixonPowerCell(df::Position(x_left + 5, getPosition().getY() + 25));
	tank1->setYVelocity(SCROLL_SPEED);
	tank2 = new NixonPowerCell(df::Position(x_left + 16, getPosition().getY() + 20));
	tank2->setYVelocity(SCROLL_SPEED);
	tank4 = new NixonPowerCell(df::Position(x_right - 16, getPosition().getY() + 20));
	tank4->setYVelocity(SCROLL_SPEED);
	tank3 = new NixonPowerCell(df::Position(x_right - 5, getPosition().getY() + 25));
	tank3->setYVelocity(SCROLL_SPEED);

	in_position = false;
	shielded = true;
}

Nixon::~Nixon() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	//Delete soldiers
	if (tank1 != NULL) {
		world_manager.markForDelete(tank1);
	}
	if (tank2 != NULL) {
		world_manager.markForDelete(tank2);
	}
	if (tank3 != NULL) {
		world_manager.markForDelete(tank3);
	}
	if (tank4 != NULL) {
		world_manager.markForDelete(tank4);
	}

	//Send Points for deletion
	df::EventView ev(SCORE_STRING, NIXON_POINTS, true);
	df::WorldManager::getInstance().onEvent(&ev);

	//Return to Level Select
	EventLevelComplete evlc;
	world_manager.onEvent(&evlc);
}

// Handle event.
// Return 0 if ignored, else 1.
int Nixon::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == FOOT_SOLDIER_DEATH_EVENT) {
		const EventFootSoldierDeath *p_death_event = dynamic_cast <EventFootSoldierDeath const *> (p_e);
		unitDied(p_death_event);
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Nixon::step() {
	if (getPosition().getY() >= 16 && !in_position) {
		setYVelocity(0);
		if (tank1 != NULL)
			tank1->setYVelocity(0);
		if (tank2 != NULL)
			tank2->setYVelocity(0);
		if (tank3 != NULL)
			tank3->setYVelocity(0);
		if (tank4 != NULL)
			tank4->setYVelocity(0);
		in_position = true;
	}

	if (tank1 == NULL && tank2 == NULL && tank3 == NULL && tank4 == NULL && in_position) {
		removeShield();
	}
}

void Nixon::removeShield() {
	shielded = false;
}

void Nixon::hit(const df::EventCollision *p_collision_event) {
	if (!shielded) {
		if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
			(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {
			health--;
			if (health <= 0) {
				df::WorldManager::getInstance().markForDelete(this);
			}
		}

		if ((p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
			(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {
			health -= 5;
			if (health <= 0) {
				df::WorldManager::getInstance().markForDelete(this);
			}
		}
	}
}

void Nixon::unitDied(const EventFootSoldierDeath *p_death_event) {
	if (tank1 == p_death_event->getSoldier()) {
		tank1 = NULL;
	}
	else if (tank2 == p_death_event->getSoldier()) {
		tank2 = NULL;
	}
	else if (tank3 == p_death_event->getSoldier()) {
		tank3 = NULL;
	}
	else if (tank4 == p_death_event->getSoldier()) {
		tank4 = NULL;
	}
}

//draw frames to match where the player is
void Nixon::draw() {
	int dir_frame = 0;
	if (shielded)
		dir_frame = 1;
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}