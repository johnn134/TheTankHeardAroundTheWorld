#include "PowerUp.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"

Ability PowerUp::getAbility() const{
	return ability;
}

PowerUp::PowerUp(Ability init_ability, df::Position p){
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	ability = init_ability;

	// Link to "power-up" sprite depending on ability
	std::string request;
	df::Sprite *p_temp_sprite;

	switch (ability){
	case WIDE_SHOT:
		request = "powerup2";
		break;
	case CANNON_CDR:
		request = "powerup1";
		break;
	case ANGLE_CANNON:
		request = "powerup3";
		break;
	default:
		request = "powerup";
		break;
	}
	p_temp_sprite = resource_manager.getSprite(request);
	if (!p_temp_sprite) {
		log_manager.writeLog("PowerUp::PowerUp(): Warning! Sprite '%s' not found", request);
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);
	}

	setPosition(p);

	setType("PowerUp");
}