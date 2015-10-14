/*
* Khrushchev.cpp
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
#include "EventLevelComplete.h"
#include "Khrushchev.h"
#include "Score.h"
#include "EnemyRocketShot.h"
#include "Jeep.h"
#include "EnemyTank.h"

Khrushchev::Khrushchev(df::Position p, df::Object *new_player) {
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "jeep" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("khrushchev");
	if (!p_temp_sprite) {
		log_manager.writeLog("Khrushchev::Khrushchev(): Warning! Sprite '%s' not found", "khrushchev");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setType("Khrushchev");

	setSolidness(df::Solidness::SOFT);

	//Register interests
	registerInterest(df::STEP_EVENT);
	registerInterest(FOOT_SOLDIER_DEATH_EVENT);

	//Set starting position
	setPosition(p);

	player = new_player;
	health = KHRUSHCHEV_HEALTH;
	health_left = KHRUSHCHEV_HEALTH / 2;
	health_right = KHRUSHCHEV_HEALTH / 2;

	jeepL = NULL;
	jeepR = NULL;
	tankM = NULL;

	fire_slowdown = 127;
	fire_countdown = fire_slowdown;

	jeep_countdown = 50;

	tank_countdown = 10;

	move_speed = 0.40f;

	in_position = false;
	going_left = false;
}

// Handle event.
// Return 0 if ignored, else 1.
int Khrushchev::eventHandler(const df::Event *p_e) {
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

void Khrushchev::step() {
	if (in_position){
		fire_countdown--;
		fire();
		if (fire_countdown < 0){
			fire_countdown = 127;
		}

		checkMove();

		jeep_countdown--;
		if (jeep_countdown == 70)
			makeJeep(true);
		if (jeep_countdown < 0){
			makeJeep(false);
			jeep_countdown = 140;
		}

		tank_countdown--;
		if (tank_countdown == 1 && tankM == NULL)
			tankM = new EnemyTank(df::Position(getPosition().getX(), getPosition().getY() + 17), player);
		if (tank_countdown < 0)
			tank_countdown = 0;
	}

	if (getPosition().getY() >= 13 && !in_position) {
		setYVelocity(0);
		setXVelocity(move_speed);
		in_position = true;
	}
}

void Khrushchev::checkMove(){
	//check if at edges of movement
	if (getPosition().getX() > df::WorldManager::getInstance().getBoundary().getHorizontal() - 54 && !going_left){
		going_left = true;
		setXVelocity(-move_speed);
	}
	else if (getPosition().getX() < 55 && going_left){
		going_left = false;
		setXVelocity(move_speed);
	}

	//check if the ears and nose are still there, if not, speed up
	if (health_left <= 0 && health_right <= 0 && move_speed < 0.50f)
		move_speed = move_speed*2;
}

void Khrushchev::fire() {
	if (fire_countdown > 20 || fire_countdown % 6 != 0)
		return;

	df::Position fire_pos(getPosition().getX(), getPosition().getY() + 15);

	EnemyRocketShot *p_r = new EnemyRocketShot(fire_pos);
	p_r->setYVelocity(1);
}

void Khrushchev::makeJeep(bool left_jeep){
	df::Position pos;

	if (left_jeep && jeepL == NULL && health_left > 0){
		pos.setXY(df::WorldManager::getInstance().getBoundary().getHorizontal() / 2 - 28, -10);
		jeepL = new Jeep(pos, player);
		jeepL->setYVelocity(0.20f);
	}
	else if(jeepR == NULL && health_right > 0){
		pos.setXY(df::WorldManager::getInstance().getBoundary().getHorizontal() / 2 + 29, -10);
		jeepR = new Jeep(pos, player);
		jeepR->setYVelocity(0.20f);
	}
}

void Khrushchev::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "PlayerGunShot") ||
		(p_collision_event->getObject2()->getType() == "PlayerGunShot")) {

		//check if left or right side is hit and still have shield up
		if (p_collision_event->getPosition().getX() < getPosition().getX() && health_left > 0){
			health_left--;
			return;
		}
		else if(health_right > 0){
			health_right--;
			return;
		}

		//ear shields are down

		health--;
			
		if (health <= 0) {
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			//Delete infantry
			if (jeepL != NULL)
				world_manager.markForDelete(jeepL);
			if (jeepR != NULL)
				world_manager.markForDelete(jeepR);
			if (tankM != NULL)
				world_manager.markForDelete(tankM);

			//Send Points for deletion
			df::EventView ev(SCORE_STRING, KHRUSHCHEV_POINTS, true);
			df::WorldManager::getInstance().onEvent(&ev);

			//Return to Level Select
			EventLevelComplete evlc;
			world_manager.onEvent(&evlc);
		}

		//Reset fire cooldown
		fire_countdown = fire_slowdown;
	}
}

void Khrushchev::soldierDied(const EventFootSoldierDeath *p_death_event) {
	if (jeepL == p_death_event->getSoldier()) {
		jeepL = NULL;
	}
	else if (jeepR == p_death_event->getSoldier()) {
		jeepR = NULL;
	}
	else if (tankM == p_death_event->getSoldier()) {
		tankM = NULL;
		tank_countdown = 150;
	}
}

//draw frames to match where the player is
void Khrushchev::draw() {
	int dir_frame = 0;
	if (health_left <= 0 && health_right > 0)
		dir_frame = 1;
	else if (health_left > 0 && health_right <= 0)
		dir_frame = 2;
	else if (health_left <= 0 && health_right <= 0)
		dir_frame = 3;
		
	df::GraphicsManager::getInstance().drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}