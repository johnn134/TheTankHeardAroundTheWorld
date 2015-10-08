#include "PlayerGunShot.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"
#include "GraphicsManager.h"

//PlayerGunShot event handler
int PlayerGunShot::eventHandler(const df::Event *p_e) {
	//Out of Bounds Event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	//event ignored
	return 0;
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

	// Set starting location, based on tank's position passed in.
	setPosition(tank_pos);
}