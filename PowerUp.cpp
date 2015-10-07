#include "PowerUp.h"
#include "ResourceManager.h"
#include "LogManager.h"

PowerUp::PowerUp(std::string init_ability, df::Position p){
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	ability = init_ability;

	// Link to "power-up" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("power-up");
	if (!p_temp_sprite) {
		log_manager.writeLog("PowerUp::PowerUp(): Warning! Sprite '%s' not found", "power-up");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(1);
	}

	setPosition(p);

	setType("PowerUp");
}