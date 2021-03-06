/*
* Mortar.cpp
*/

//System Headers
#include <stdlib.h>

//Dragonfly Headers
#include "EventStep.h"
#include "EventView.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "EnemyBombShot.h"
#include "EventFootSoldierDeath.h"
#include "Mortar.h"
#include "Score.h"
#include "SmallExplosion.h"

Mortar::Mortar(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "mortar" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("mortar");
	if (!p_temp_sprite) {
		log_manager.writeLog("Mortar::Mortar(): Warning! Sprite '%s' not found", "mortar");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Mortar");

	setSolidness(df::Solidness::SOFT);

	//Set starting position
	setPosition(p);

	player = new_player;
	fire_slowdown = 60;
	fire_countdown = fire_slowdown;
	firing_anim_slowdown = 5;
	firing_anim_countdown = firing_anim_slowdown;
	occupied = true;
	firing = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int Mortar::eventHandler(const df::Event *p_e) {
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

void Mortar::step() {
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;

	//Firing animation countdown
	firing_anim_countdown--;
	if (firing_anim_countdown < 0)
		firing_anim_countdown = 0;

	//See if firing is finished
	if (firing_anim_countdown <= 0) {
		firing = false;
	}
}

void Mortar::fire() {
	//Only fire if a soldier to occupying the mortar
	if (occupied) {
		// See if time to fire.
		if (fire_countdown > 0)
			return;

		//Reset countdown
		fire_countdown = fire_slowdown + (int)(rand() % 10);

		//Check if player is in range
		int y_offset = player->getPosition().getY() - getPosition().getY();

		if (y_offset > 0 && boxIntersectsBox(getWorldBox(this), df::WorldManager::getInstance().getView())) {
			// Fire bomb on player
			EnemyBombShot *p = new EnemyBombShot(player->getPosition());

			//Reset countdown
			firing_anim_countdown = firing_anim_slowdown;
			firing = true;

			// Play "fire" sound.
		}
	}
}

void Mortar::hit(const df::EventCollision *p_collision_event) {
	// If PlayerGunShot, kill occupant
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot" ||
		p_collision_event->getObject2()->getType() == "PlayerGunShot") && occupied) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		//Kill occupant
		occupied = false;

		//Send Points for deletion
		df::EventView ev(SCORE_STRING, MORTAR_UNOCCUPY_POINTS, true);
		world_manager.onEvent(&ev);

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());
	}

	// If Tank or PlayerCannonShot, create explosion and delete mortar
	if ((p_collision_event->getObject1()->getType() == "Tank") ||
		(p_collision_event->getObject2()->getType() == "Tank") ||
		(p_collision_event->getObject1()->getType() == "PlayerCannonShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerCannonShot")) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();

		// Create an explosion.
		SmallExplosion *p_explosion = new SmallExplosion(getPosition());

		// Play "explode" sound

		//Send Points for deletion
		df::EventView ev(SCORE_STRING, MORTAR_DESTROY_POINTS, true);
		world_manager.onEvent(&ev);

		//Send death event
		EventFootSoldierDeath efsd(this);
		world_manager.onEvent(&efsd);

		//Delete this object
		world_manager.markForDelete(this);
	}
}

//draw frames to match where the player is
void Mortar::draw(void) {
	int dir_frame = 0;
	if (!occupied) {
		dir_frame = 0;
	}
	else {
		if (!firing)
			dir_frame = 1;
		else
			dir_frame = 2;
	}
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}