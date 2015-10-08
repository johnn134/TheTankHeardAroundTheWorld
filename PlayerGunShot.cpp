#include "PlayerGunShot.h"
#include "SmallExplosion.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventView.h"
#include "GraphicsManager.h"

//PlayerGunShot event handler
int PlayerGunShot::eventHandler(const df::Event *p_e) {
	//Out of Bounds Event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	//catch collision events
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_event_collision = static_cast <const df::EventCollision *> (p_e);

		hit(p_event_collision);
		return 1;
	}

	//event ignored
	return 0;
}

void PlayerGunShot::hit(const df::EventCollision *p_collision_event) {
	if (p_collision_event->getObject1()->getType() != "EnemyCannonShot" &&
		p_collision_event->getObject2()->getType() != "EnemyCannonShot" &&
		p_collision_event->getObject1()->getType() != "BarbWire" &&
		p_collision_event->getObject2()->getType() != "BarbWire" &&
		p_collision_event->getObject1()->getType() != "PowerUp" &&
		p_collision_event->getObject2()->getType() != "PowerUp" &&
		p_collision_event->getObject1()->getType() != "Helicopter" &&
		p_collision_event->getObject2()->getType() != "Helicopter" &&
		p_collision_event->getObject1()->getType() != "EnemyGunShot" &&
		p_collision_event->getObject2()->getType() != "EnemyGunShot" &&
		p_collision_event->getObject1()->getType() != "Tank" &&
		p_collision_event->getObject2()->getType() != "Tank" &&
		p_collision_event->getObject1()->getType() != "PlayerCannonShot" &&
		p_collision_event->getObject2()->getType() != "PlayerCannonShot") {
		df::WorldManager &world_manager = df::WorldManager::getInstance();

		//Play gun impact sound
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("gun-impact");
		p_sound->play();

		world_manager.markForDelete(this);
	}
}

//PlayerGunShot is out of bounds, mark for deletion
void PlayerGunShot::out(){
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

//PlayerGunShot constructor
PlayerGunShot::PlayerGunShot(df::Position tank_pos){
	//needed managers
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Link to "player-gun-shot" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("playergunshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("PlayerGunShot::PlayerGunShot(): Warning! Sprite '%s' not found", "playergunshot");
	}
	else {
		setSprite(p_temp_sprite);
		setTransparency();	   // Transparent sprite.
	}

	//define type
	setType("PlayerGunShot");

	setSolidness(df::SOFT);

	registerInterest(df::OUT_EVENT);
	registerInterest(df::COLLISION_EVENT);

	// Set starting location, based on tank's position passed in.
	setPosition(tank_pos);
}