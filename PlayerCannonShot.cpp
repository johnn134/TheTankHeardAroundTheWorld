#include "PlayerCannonShot.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"
#include "GraphicsManager.h"

//PlayerCannonShot event handler
int PlayerCannonShot::eventHandler(const df::Event *p_e) {
	//Out of Bounds Event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	//event ignored
	return 0;
}

//PlayerCannonShot is out of bounds, mark for deletion
void PlayerCannonShot::out(){
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

//PlayerCannonShot constructor
PlayerCannonShot::PlayerCannonShot(df::Position tank_pos){
	//needed managers
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Link to "player-cannon-shot" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("playercannonshot");
	if (!p_temp_sprite) {
		log_manager.writeLog("PlayerCannonShot::PlayerCannonShot(): Warning! Sprite '%s' not found", "playercannonshot");
	}
	else {
		setSprite(p_temp_sprite);
		setTransparency();	   // Transparent sprite.
	}

	//define type
	setType("PlayerCannonShot");

	setSolidness(df::SOFT);

	registerInterest(df::OUT_EVENT);

	// Set starting location, based on tank's position passed in.
	tank_pos.setY(tank_pos.getY() - 1);
	setPosition(tank_pos);
}